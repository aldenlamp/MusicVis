//
// Created by alden lamp on 11/17/20.
//

#ifndef FINAL_PROJECT_SONG_H
#define FINAL_PROJECT_SONG_H

#include "Resources.h"
#include "cinder/gl/gl.h"
#include "cinder/audio/audio.h"
#include "cinder/app/App.h"


namespace musicvis_model {

using ci::audio::BufferPlayerNodeRef;
using ci::audio::MonitorSpectralNodeRef;
using ci::audio::MonitorSpectralNode;
using ci::audio::SourceFileRef;
using ci::audio::BufferRef;
using std::vector;
using glm::vec2;

enum song_names {
  Amber, FeelsLike, TimeAloneWith, Borderline, Nangs, Fkj
};

// Frames to use for blurring
const double kHorizontalBlurFrame[]{0.1, 0.2, 0.4, 0.2, 0.1};
const double kBackBlurFrame[]{0.3, 0.2, 0.15, 0.15, 0.1, 0.05, 0.05};

class Song {

public:

  /**
   * Creates a song
   * @param bins the number of bins to analyze the song into
   * @param name the name of the song to use
   * @param fft_size the size (accuracy) of the fft
   * @param window_size the size of the frame to analyze every time
   * @param analysis_window the window to use from the analysis
   */
  Song(size_t bins, song_names name = Amber, size_t fft_size = 2048, size_t window_size = 1024,
       vec2 analysis_window = vec2(8, 1024));

  /**
   * Plays the song or pauses the song depending on if it is currently playing
   */
  void Play();

  /**
   * Stops the song and starts it from scratch
   */
  void Reset();

  /**
   * Getter for the analysis of the current position in the song
   * @return
   */
  vector<double> GetBins();

  /**
   * Getter for the current volume of the song
   * @return a float representing the volume
   */
  float GetVolume() const;

private:

  // Blurs one row of bins using the horizontal blur fram
  void BlurSideways(vector<double> &bins);

  // Blurs the given row of bins with the past few rows using the back blur frame
  void BlurBackward(vector<double> &bins);

  // Stores the last rows of bins for blurring
  vector<vector<double>> last_bins_;

  // Audio node to play and analyze the song
  BufferPlayerNodeRef player_node_;
  MonitorSpectralNodeRef monitor_node_;

  // Analysis setting
  size_t num_bins_;
  vec2 analysis_window_;

  // Info for pausing and playing
  bool is_playing_;
  double play_position_;


};


}


#endif //FINAL_PROJECT_SONG_H
