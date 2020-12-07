//
// Created by alden lamp on 11/17/20.
//


#include <model/song.h>

namespace musicvis_model{

Song::Song(song_names name, size_t fft_size, size_t window_size) {
  auto ctx = ci::audio::Context::master();

  SourceFileRef sourceFile = ci::audio::load(ci::app::loadResource(FLUME_AMBER), ctx->getSampleRate());
  BufferRef buffer = sourceFile->loadBuffer();
  player_node_ = ctx->makeNode(new ci::audio::BufferPlayerNode(buffer));

  MonitorSpectralNode::Format format = MonitorSpectralNode::Format().fftSize(fft_size).windowSize(window_size);
  monitor_node_ = ctx->makeNode(new ci::audio::MonitorSpectralNode(format));

  player_node_ >> monitor_node_;
  player_node_ >> ctx->getOutput();
  ctx->enable();
}

void Song::Play() {
  player_node_->start();
}

void Song::Stop() {
  player_node_->stop();
}

const vector<float> & Song::GetFFTResult() {
  return monitor_node_->getMagSpectrum();
}


}
