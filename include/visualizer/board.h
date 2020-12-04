//
// Created by alden lamp on 12/4/20.
//

#ifndef FINAL_PROJECT_BOARD_H
#define FINAL_PROJECT_BOARD_H

#include "cinder/gl/gl.h"

namespace visualizer{

using glm::vec2;
using ci::Color;
using std::vector;

class Board {

public:
  Board(vec2 dimensions);

  void SetPixel(size_t x, size_t y, Color color);

  void FillBoard(Color color);

  void FillBoard(const vector<vector<Color>> &board);

  void Resize(vec2 size);

  void Draw() const;

  // For testing purposes only
  const vector<vector<Color>> GetBoard() const;

private:
  vec2 display_size_;
  vec2 board_dimensions;
  vec2 pixel_dimensions;
  vector<vector<Color>> board;

};


}



#endif //FINAL_PROJECT_BOARD_H
