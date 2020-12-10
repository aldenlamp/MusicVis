//
// Created by alden lamp on 11/17/20.
//

#include <controller/musicvis_controller.h>

namespace controller {

void MusicVisController::setup() {
  ci::app::getWindow()->setTitle("music_vis");

  // Setting up the song
  song_ = Song(kBoardDimensions[0] / 2, kSongName);
  switch (kSongName) {
    case TimeAloneWith:
      sensitivity_ *= 2;
    case Nangs:
      sensitivity_ *= 2;
    default:
      break;
  }

  // Setting up the board
  vec2 window_size = ci::app::getWindowBounds().getSize();
  board_ = Board(kBoardDimensions, window_size);

  // Setting up the gradient
  vector<Color> colors{Color("Blue"), Color("Red"), Color("Indigo"), Color(0, 1, 0)};
  gradient_ = GradientLine(colors, kGradientFunction);
}

void MusicVisController::update() {

  // Cycles colors if necessary and possible
  if (song_.GetVolume() * color_change_sensitivity_ > kVolumeThreshold) {
    if (count_since_color_change_ > kColorChangeFrameLimit) {
      count_since_color_change_ = 1;
    }
    if (count_since_color_change_ < kColorChangeFrameLimit) {
      gradient_.Step(kColorChangeStep);
    }
  }
  count_since_color_change_++;

  // Gets current song info and updates it to the board
  vector<double> divs = song_.GetBins();
  for (size_t i = 0; i < kBoardDimensions[0] / 2; i++) {
    size_t y = divs[i] * sensitivity_ * kBoardDimensions[1] * kBoardDimensions[0];

    size_t mid = (kBoardDimensions[1] - 1) / 2;

    // Chooses the color of this horizontal strip
    Color curr = gradient_.GetColorAtPosition(divs[i] * sensitivity_ * kBoardDimensions[0] / kBoardDimensions[1]);

    // Updates the Board
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
  // Draws the visual to cinder
  board_.Draw();

  // Adds sensitivity info to the bottom left
  vec2 window_size = ci::app::getWindowBounds().getSize();
  ci::gl::drawString("Sensitivity: " + std::to_string(sensitivity_), vec2(5, window_size[1] - 30));
  ci::gl::drawString("Color Change Sensitivity: " + std::to_string((size_t) (color_change_sensitivity_ * 10)),
                     vec2(5, window_size[1] - 15));
}

void MusicVisController::resize() {
  // Resizes the board
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