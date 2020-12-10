//
// Created by alden lamp on 11/17/20.
//


#include <model/song.h>

namespace musicvis_model {

Song::Song(size_t bins, song_names name, size_t fft_size, size_t window_size, vec2 analysis_window) {
  // Loads the song resource from the song name
  auto resource = ci::app::loadResource(FLUME_AMBER);
  switch (name) {
    case FeelsLike:
      resource = ci::app::loadResource(FLWOGB);
      break;
    case TimeAloneWith:
      resource = ci::app::loadResource(TIME_ALONE);
      break;
    case Borderline:
      resource = ci::app::loadResource(BORDERLINE);
      break;
    case Nangs:
      resource = ci::app::loadResource(NANGS);
      break;
    default:
      break;
  }

  is_playing_ = false;

  // Sets up the player node
  auto ctx = ci::audio::Context::master();
  SourceFileRef sourceFile = ci::audio::load(resource, ctx->getSampleRate());
  BufferRef buffer = sourceFile->loadBuffer();
  player_node_ = ctx->makeNode(new ci::audio::BufferPlayerNode(buffer));
  player_node_ >> ctx->getOutput();

  // Sets up the monitor node
  MonitorSpectralNode::Format format = MonitorSpectralNode::Format().fftSize(fft_size).windowSize(window_size);
  monitor_node_ = ctx->makeNode(new ci::audio::MonitorSpectralNode(format));
  player_node_ >> monitor_node_;

  ctx->enable();

  // Saves analysis info
  num_bins_ = bins;
  analysis_window_ = analysis_window;
}

void Song::Play() {
  if (!is_playing_) {
    player_node_->start();
    player_node_->seek(play_position_);
    is_playing_ = true;
  } else {
    play_position_ = player_node_->getReadPosition();
    player_node_->stop();
    is_playing_ = false;
  }
}

void Song::Reset() {
  if (is_playing_) {
    player_node_->stop();
    is_playing_ = false;
  }
  play_position_ = 0;
}

vector<double> Song::GetBins() {
  // Gets raw fft data from the monitor node
  const vector<float> &spect = monitor_node_->getMagSpectrum();

  // Groups the data into bins logarithmically (to represent the data more like musical notes)

  // Processes teh analysis window logarithmically
  double start = log2(analysis_window_[0]);
  double end = log2(analysis_window_[1]);
  double div_size = (end - start) / num_bins_;

  vector<double> bins = vector<double>();

  // Groups the data into bins
  double sum = 0;
  size_t curr_bin = 0;
  for (size_t i = analysis_window_[0]; i < analysis_window_[1]; i++) {
    size_t window = (log2(i) - start) / div_size;
    if (window >= curr_bin) {
      curr_bin++;
      bins.push_back(sum * sum);
      sum = 0;
    }
    sum += spect[i];
  }

  // Blurs the bins sideways and backwards
  BlurSideways(bins);
  BlurBackward(bins);

  return bins;
}


void Song::BlurSideways(vector<double> &bins) {
  // Size of the blur on each side
  size_t blur_size = (sizeof(kHorizontalBlurFrame) / sizeof(kHorizontalBlurFrame[0]) - 1) / 2;
  vector<double> blurred;

  for (size_t i = 0; i < bins.size(); i++) {
    double new_value = 0;

    // Handles the first few items before with a cut off blur filter
    if (i < blur_size) {
      double blur_sum = 0;
      for (size_t j = 0; j < blur_size + i; j++) {
        size_t blur_index = (blur_size - i) + j;
        new_value += kHorizontalBlurFrame[blur_index] * bins[j];
        blur_sum += kHorizontalBlurFrame[blur_index];
      }
      blurred.push_back(new_value / blur_sum);
      continue;
    }

    // Handles normal cases and last few items
    double blur_sum = 0;
    for (size_t j = i - blur_size; j < ((i + blur_size > bins.size()) ? bins.size() : i + blur_size); j++) {
      size_t blur_index = (j - i) + blur_size;
      new_value += kHorizontalBlurFrame[blur_index] * bins[j];
      blur_sum += kHorizontalBlurFrame[blur_index];
    }
    blurred.push_back(new_value / blur_sum);
  }

  // Updates given bins with blurred bins
  for (size_t i = 0; i < bins.size(); i++) {
    bins[i] = blurred[i];
  }
};

void Song::BlurBackward(vector<double> &bins) {
  // Size of the blur
  size_t blur_size = sizeof(kBackBlurFrame) / sizeof(kBackBlurFrame[0]);
  vector<double> blurred;

  // Blurring with the last few bins
  for (size_t i = 0; i < bins.size(); i++) {
    double blur_sum = 0;
    double value = 0;
    for (size_t j = 0; j < last_bins_.size(); j++) {
      if (j == 0) {
        value += kBackBlurFrame[j] * bins[i];
      } else if (j == 1) {
        double greater = last_bins_[j - 1][i] > bins[i] ? last_bins_[j - 1][i] : bins[i];
        value += kBackBlurFrame[j] * greater;
      } else {
        value += kBackBlurFrame[j] * last_bins_[j - 1][i];
      }
      blur_sum += kBackBlurFrame[j];
    }
    blurred.push_back(value / blur_sum);

  }

  // Updating the given bins with the blurred version
  for (size_t i = 0; i < bins.size(); i++) {
    bins[i] = blurred[i];
  }

  // Updating the last_bins vector
  last_bins_.insert(last_bins_.begin(), blurred);
  if (last_bins_.size() >= blur_size - 1) {
    last_bins_.pop_back();
  }
}

float Song::GetVolume() const {
  return monitor_node_->getVolume();
}

}
