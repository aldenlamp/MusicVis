//
// Created by alden lamp on 12/4/20.
//

#ifndef FINAL_PROJECT_GRADIENT_LINE_H
#define FINAL_PROJECT_GRADIENT_LINE_H

#include "cinder/gl/gl.h"

namespace visualizer {

namespace gradient{

using glm::vec2;
using ci::Color;
using std::vector;

enum line_function {Line, Sine, Cosine, Square, Quad, Sqrt};

const double kFuncApproximationConst = 0.01;

class GradientLine{

public:

  GradientLine();

  GradientLine(const vector<Color> &colors, line_function function = Line, vec2 domain = vec2(0.0, 1.0));

  GradientLine(const vector<Color> &colors, const vector<double> &positions, line_function function = Line, vec2 domain = vec2(0.0, 1.0));

  void AddColor(Color color, double position);

  void ChangeColor(size_t index, Color color);

  void Step(double proportion);

  Color GetColorAtPosition(double position);

  void Print() const;

private:
  double ScaledLineFunction(double x) const;
  double LineFunction(line_function func, double x) const;

  vec2 ApproximateFunctionRange(line_function func, vec2 domain);

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
