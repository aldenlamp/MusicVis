//
// Created by alden lamp on 12/4/20.
//

#ifndef FINAL_PROJECT_BOARD_H
#define FINAL_PROJECT_BOARD_H

#include "cinder/gl/gl.h"

namespace visualizer {

using glm::vec2;
using ci::Color;
using std::vector;

class Board {

public:
  /**
   * Initializes an empty board
   */
  Board();

  /**
   * Creates a board with the given dimensions and display size
   * @param board_dimensions the dimensions of the board
   * @param board_size the dimensions of the display window
   */
  Board(vec2 board_dimensions, vec2 board_size);

  /**
   * Sets a pixel a given color
   * @param x the x coordinate
   * @param y they y coordinate
   * @param color the color to set that pixel
   */
  void SetPixel(size_t x, size_t y, Color color);

  /**
   * Fills the entire board with one color
   * @param color to fill the board with
   */
  void FillBoard(Color color);

  /**
   * Fills the entire board based on the given vector
   * @param board the vector of vectors of colors to fill the board with
   */
  void FillBoard(const vector<vector<Color>> &board);

  /**
   * Resizes the board given the new display window size
   * @param size the display window size to fill the board with
   */
  void Resize(vec2 size);

  /**
   * Draws the board to cinder
   */
  void Draw() const;

  /**
   * Returns a representation of the board
   * For testing purposes only
   * @return a vector of vectors of Colors representing the board
   */
  const vector<vector<Color>> GetBoard() const;

  /**
   * Getter for the size of each individual rectangle on the board
   * @return a vec2 for the pixel dimensions
   */
  vec2 GetPixelDimensions() const;

private:
  vec2 board_dimensions_;
  vec2 pixel_dimensions_;
  vector<vector<Color>> board_;

};
}

#endif //FINAL_PROJECT_BOARD_H
