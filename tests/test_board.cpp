//
// Created by alden lamp on 12/4/20.
//
#include <catch2/catch.hpp>
#include <visualizer/board.h>

#inlcude "ci/gl/gl.h"

/*
 * Testing Strategy
 * Constructor tests:
 *   Correct Board Size
 * Set Pixel:
 *   Correct pixel set
 * Fill Board:
 *   Solid color, Preset color
 */

using visualizer::Board;
using glm::vec2;
using ci::Color;
using std::vector;

TEST_CASE ("Board Constructor tests") {
  SECTION ("Correct Board Size") {
    Board b = Board(vec2(10, 15));
    vector<vector<Color>> board = b.GetBoard();

    REQUIRE(board.size() == 10);
    REQUIRE(board.at(0).size() == 15);

    for (size_t row = 0; row < 10; row++) {
      for (size_t col = 0; col < 15; col++) {
        REQUIRE(board.at(row).at(col) == Color("white"));
      }
    }
  }
}

TEST_CASE ("Set Pixel") {
  SECTION ("Correctly sets") {
    Board b = Board(vec2(10, 15));
    b.SetPixel(7, 8, Color("black"));
    vector<vector<Color>> board = b.GetBoard();

    for (size_t row = 0; row < 10; row++) {
      for (size_t col = 0; col < 15; col++) {
        if (row == 7 && col == 8) {
          REQUIRE(board.at(row).at(col) == Color("white"));
        } else {
          REQUIRE(board.at(row).at(col) == Color("white"));
        }
      }
    }
  }
}

TEST_CASE ("Fill Board") {
  SECTION("Solid Color") {
    Board b = Board(vec2(10, 15));
    b.FillBoard(Color("red"));
    vector<vector<Color>> board = b.GetBoard();

    for (size_t row = 0; row < 10; row++) {
      for (size_t col = 0; col < 15; col++) {
        REQUIRE(board.at(row).at(col) == Color("red"));
      }
    }
  }

  SECTION ("Preset Color") {
    Board b = Board(vec2(2, 3));
    vector<vector<Color>> preset = vector<vector<Color>>();
    preset.push_back(vector<Color>());
    preset.push_back(vector<Color>());
    preset[0].push_back(Color("red"));
    preset[0].push_back(Color("green"));
    preset[0].push_back(Color("blue"));
    preset[1].push_back(Color("pink"));
    preset[1].push_back(Color("black"));
    preset[1].push_back(Color("orange"));

    b.FillBoard(preset);
    vector<vector<Color>> board = b.GetBoard();

    REQUIRE(preset == board);
  }
}