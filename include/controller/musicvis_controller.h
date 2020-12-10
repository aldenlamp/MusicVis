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
#include "cinder/app/App.h"
#include "cinder/audio/audio.h"

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
using musicvis_model::song_names::Fkj;

const vec2 kBoardDimensions(128, 7);
const song_names kSongName = Amber;

const double kVolumeThreshold = 0.4;
const size_t kColorChangeFrameLimit = 10;
const double kColorChangeStep = 0.073;
const line_function kGradientFunction = Sqrt;

class MusicVisController : public ::ci::app::App {

public:
  void setup() override;

  void draw() override;

  void update() override;

  void resize() override;

  void keyDown(ci::app::KeyEvent event) override;

private:

  Song song_ = Song(kBoardDimensions[0]);

  Board board_;

  GradientLine test_gradient_;
  size_t count_since_color_change_;

  size_t sensitivity_ = 10;
  double color_change_sensitivity_ = 1;
};

}

#endif //FINAL_PROJECT_MUSICVIS_CONTROLLER_H
