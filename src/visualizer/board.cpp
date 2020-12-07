//
// Created by alden lamp on 12/4/20.
//

#include <visualizer/board.h>

namespace visualizer {

Board::Board() {
  Board(vec2(0, 0), vec2(0, 0));
}

Board::Board(vec2 board_dimensions, vec2 board_size) {
  board_dimensions_ = board_dimensions;
  Resize(board_size);
  for (size_t x = 0; x < board_dimensions_[0]; x++) {
    board_.push_back(vector<Color>());
    for (size_t y = 0; y < board_dimensions_[1]; y++) {
      board_[x].push_back(Color("white"));
    }
  }
}

void Board::SetPixel(size_t x, size_t y, Color color) {
  board_.at(x).at(y) = color;
}

void Board::FillBoard(Color color) {
  for (size_t x = 0; x < board_dimensions_[0]; x++) {
    for (size_t y = 0; y < board_dimensions_[1]; y++) {
      board_[x][y] = color;
    }
  }
}

void Board::FillBoard(const vector<vector<Color>> &board) {
  for (size_t x = 0; x < board_dimensions_[0]; x++) {
    for (size_t y = 0; y < board_dimensions_[1]; y++) {
      board_[x][y] = board.at(x).at(y);

    }
  }
}

void Board::Resize(vec2 size) {
  double_t pixel_width = size[0] / board_dimensions_[0];
  double_t pixel_height = size[1] / board_dimensions_[1];
  pixel_dimensions_ = vec2(pixel_width, pixel_height);
}

void Board::Draw() const {
  ci::gl::clear(Color("white"));
  for (size_t col = 0; col < board_dimensions_[0]; col++) {
    for (size_t row = 0; row < board_dimensions_[1]; row++) {
      ci::gl::color(board_[col][row]);

      vec2 pixel_top_left(col * pixel_dimensions_[0], row * pixel_dimensions_[1]);
      vec2 pixel_bottom_right = pixel_top_left + pixel_dimensions_;
      ci::Rectf bounding_box(pixel_top_left, pixel_bottom_right);

      ci::gl::drawSolidRect(bounding_box);
//      ci::gl::color(ci::Color("black"));
//      ci::gl::drawStrokedRect(bounding_box);
    }
  }
}

const vector<vector<Color>> Board::GetBoard() const {
  return board_;
}

vec2 Board::GetPixelDimensions() const {
  return pixel_dimensions_;
}

}