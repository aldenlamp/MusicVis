//
// Created by alden lamp on 12/4/20.
//

#ifndef FINAL_PROJECT_GRADIENT_LINE_H
#define FINAL_PROJECT_GRADIENT_LINE_H

#include "cinder/gl/gl.h"

namespace visualizer {

namespace gradient {

using glm::vec2;
using ci::Color;
using std::vector;

enum line_function {
  Line, Sine, Cosine, Square, Quad, Sqrt
};

// For finding the maximum values of functions
const double kFuncApproximationConst = 0.01;

class GradientLine {
public:

  /**
   * Empty constructor that creates a black and white gradient
   */
  GradientLine();

  /**
   * Creates a gradient with evenly spaced colors
   * @param colors the colors to create the gradient with
   * @param function the function to use for evaluation
   * @param domain the domain of the function to use
   */
  GradientLine(const vector<Color> &colors, line_function function = Line, vec2 domain = vec2(0.0, 1.0));

  /**
   * Creates a gradient with custom colors and distances
   * @param colors the colors to use
   * @param positions a list of positions from 0.0 to 2.0 representing the color spacing
   * @param function the function to use for evaluation
   * @param domain the domain of the function to use
   */
  GradientLine(const vector<Color> &colors, const vector<double> &positions, line_function function = Line,
               vec2 domain = vec2(0.0, 1.0));

  /**
   * Adds a color to the gradient list
   * @param color the color to add
   * @param position the position to add it in
   */
  void AddColor(Color color, double position);

  /**
   * Changes a color in the list
   * @param index the current index of the color to change
   * @param color the color to change it to
   */
  void ChangeColor(size_t index, Color color);

  /**
   * Cycles the function by half the given proportion
   * @param proportion the proportion to cycle with
   */
  void Step(double proportion);

  /**
   * Evaluates the color at the given position
   * @param position the position to evaluate at
   * @return a Color created from interpolating the closest colors
   */
  Color GetColorAtPosition(double position);

private:
  // Calls the given function scaling the range and domain to be between 0 and 1
  double ScaledLineFunction(double x) const;

  // Calls the given function
  double LineFunction(line_function func, double x) const;

  // Approximates the range of the function to be used for scalling later
  vec2 ApproximateFunctionRange(line_function func, vec2 domain);

  // Sorts the colors and color_positions in order of their non-function position
  void SortColors();

  vector<Color> colors_;
  vector<double> color_positions_;

  line_function function_;
  vec2 function_domain_;
  vec2 function_range_;


};

}

}


#endif //FINAL_PROJECT_GRADIENT_LINE_H
