//
// Created by alden lamp on 11/17/20.
//

#include <controller/musicvis_controller.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGL.h"
#include "cinder/gl/gl.h"

#include "cinder/audio/Voice.h"
#include "cinder/audio/Source.h"

#include "Resources.h"

namespace controller {

void MusicVisController::setup() {
  ci::app::getWindow()->setTitle("music_vis");
  vec2 window_size = ci::app::getWindowBounds().getSize();

  switch (kSongName) {
    case TimeAloneWith:
      sensitivity_ *= 2;
    case Nangs:
      sensitivity_ *= 2;
    case Fkj:
      sensitivity_ *= 5;
    default:
      break;
  }

  song_ = Song(kBoardDimensions[0] / 2, kSongName);
  board_ = Board(kBoardDimensions, window_size);

  vector<Color> colors = vector<Color>();
  colors.push_back(Color("Blue"));
  colors.push_back(Color("Red"));
  colors.push_back(Color("Indigo"));
  colors.push_back(Color(0, 1, 0));

  test_gradient_ = GradientLine(colors, kGradientFunction);
}

void MusicVisController::update() {
  count_since_color_change_++;
  if (song_.GetVolume() * color_change_sensitivity_ > kVolumeThreshold) {
    if (count_since_color_change_ > kColorChangeFrameLimit) {
      count_since_color_change_ = 0;
    }
    if (count_since_color_change_ < kColorChangeFrameLimit) {
      test_gradient_.Step(kColorChangeStep);
    }
  }

  vector<double> divs = song_.GetBins();
  for (size_t i = 0; i < kBoardDimensions[0] / 2; i++) {
    size_t y = divs[i] * sensitivity_ * kBoardDimensions[1] * kBoardDimensions[0];

    size_t mid = (kBoardDimensions[1] - 1) / 2;

    Color curr = test_gradient_.GetColorAtPosition(divs[i] * sensitivity_ * kBoardDimensions[0] / kBoardDimensions[1]);

    for (size_t j = mid; j < kBoardDimensions[1]; j++) {
      if (y / 2 > j - mid) {
        board_.SetPixel(kBoardDimensions[0] / 2 + i, j, curr);
        board_.SetPixel(kBoardDimensions[0] / 2 - 1 - i, j, curr);
        if (j != mid) {
          board_.SetPixel(kBoardDimensions[0] / 2 + i, kBoardDimensions[1] - 1 - j, curr);
          board_.SetPixel(kBoardDimensions[0] / 2 - 1 - i, kBoardDimensions[1] - 1 - j, curr);
        }
      } else {
        board_.SetPixel(kBoardDimensions[0] / 2 + i, kBoardDimensions[1] - 1 - j, Color("black"));
        board_.SetPixel(kBoardDimensions[0] / 2 + i, j, Color("black"));
        board_.SetPixel(kBoardDimensions[0] / 2 - 1 - i, kBoardDimensions[1] - 1 - j, Color("black"));
        board_.SetPixel(kBoardDimensions[0] / 2 - 1 - i, j, Color("black"));
      }
    }
  }

}

void MusicVisController::draw() {
  board_.Draw();

  vec2 window_size = ci::app::getWindowBounds().getSize();

  ci::gl::drawString("Sensitivity: " + std::to_string(sensitivity_), vec2(5, window_size[1] - 30));
  ci::gl::drawString("Color Change Sensitivity: " + std::to_string((size_t) (color_change_sensitivity_ * 10)),
                     vec2(5, window_size[1] - 15));
}

void MusicVisController::resize() {
  vec2 window_size = ci::app::getWindowBounds().getSize();
  board_.Resize(window_size);
}

void MusicVisController::keyDown(ci::app::KeyEvent event) {

  if (event.getCode() == ci::app::KeyEvent::KEY_SPACE) {
    song_.Play();
  }

  if (event.getCode() == ci::app::KeyEvent::KEY_r) {
    song_.Reset();
  }

  if (event.getCode() == ci::app::KeyEvent::KEY_UP) {
    sensitivity_ += 2;
  }

  if (event.getCode() == ci::app::KeyEvent::KEY_DOWN) {
    sensitivity_ -= 2;
  }

  if (event.getCode() == ci::app::KeyEvent::KEY_RIGHT) {
    color_change_sensitivity_ += 0.1;
  }
  if (event.getCode() == ci::app::KeyEvent::KEY_LEFT) {
    color_change_sensitivity_ -= 0.1;
  }


}

}