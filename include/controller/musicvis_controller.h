//
// Created by alden lamp on 11/17/20.
//

#ifndef FINAL_PROJECT_MUSICVIS_CONTROLLER_H
#define FINAL_PROJECT_MUSICVIS_CONTROLLER_H

#include <visualizer/board.h>
#include <visualizer/gradient_line.h>
#include <model/song.h>

#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGL.h"
#include "cinder/audio/audio.h"
#include "cinder/audio/Source.h"

namespace controller {

using glm::vec2;
using ci::Color;
using std::vector;

using ci::audio::VoiceRef;
using ci::audio::SourceFileRef;

using visualizer::Board;
using visualizer::gradient::GradientLine;
using visualizer::gradient::line_function;
using visualizer::gradient::Line;
using visualizer::gradient::Sine;
using visualizer::gradient::Cosine;
using visualizer::gradient::Square;
using visualizer::gradient::Quad;
using visualizer::gradient::Sqrt;

using musicvis_model::Song;
using musicvis_model::song_names;
using musicvis_model::song_names::Amber;
using musicvis_model::song_names::FeelsLike;
using musicvis_model::song_names::TimeAloneWith;
using musicvis_model::song_names::Borderline;
using musicvis_model::song_names::Nangs;

// The song to use
const song_names kSongName = Amber;

// Dimensions for the visualizer
const vec2 kBoardDimensions(128, 7);

// Percent volume needed to change colors
const double kVolumeThreshold = 0.4;

// Amount of frames needed between color changes
const size_t kColorChangeFrameLimit = 10;

// Percent to shift the gradient when changing colors
const double kColorChangeStep = 0.073;

// Gradient evaluation function to use
const line_function kGradientFunction = Sqrt;

class MusicVisController : public ::ci::app::App {

public:
  /**
   * Sets up the MusicVisController
   */
  void setup() override;

  /**
   * Draws the board with Cinder
   */
  void draw() override;

  /**
   * Updates the board from the song analysis
   */
  void update() override;

  /**
   * Resizes the board
   */
  void resize() override;

  /**
   * Handles inputs
   * these inlcude space to pause and play, r to reset, and the arrow keys to adjust sensitivity
   * @param event the key event to be processed
   */
  void keyDown(ci::app::KeyEvent event) override;

private:

  Song song_ = Song(kBoardDimensions[0]);

  Board board_;

  GradientLine gradient_;
  size_t count_since_color_change_;

  size_t sensitivity_ = 10;
  double color_change_sensitivity_ = 1;
};

}

#endif //FINAL_PROJECT_MUSICVIS_CONTROLLER_H
