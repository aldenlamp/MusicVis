//
// Created by alden lamp on 12/4/20.
//

#include <visualizer/gradient_line.h>

namespace visualizer {

namespace gradient {

GradientLine::GradientLine() : function_(Line), function_domain_(vec2(0.0, 1.0)), function_range_(0.0, 1.0) {
  colors_.push_back(Color("black"));
  color_positions_.push_back(0.0);

  colors_.push_back(Color("white"));
  color_positions_.push_back(1.0);
}

GradientLine::GradientLine(const vector<Color> &colors, line_function function, vec2 domain) : function_(function),
                                                                                               function_domain_(domain),
                                                                                               function_range_(
                                                                                                   ApproximateFunctionRange(
                                                                                                       function,
                                                                                                       domain)) {
  colors_ = colors;

  // Evenly spaces out the colors
  double num_colors = colors.size();
  double div_dist = 2.0 / num_colors;
  for (size_t div = 0; div < num_colors; div++) {
    color_positions_.push_back(div * div_dist);
  }
}

GradientLine::GradientLine(const vector<Color> &colors, const vector<double> &positions, line_function function,
                           vec2 domain) : function_(function), function_domain_(domain),
                                          function_range_(ApproximateFunctionRange(function, domain)) {
  colors_ = colors;
  color_positions_ = positions;
}

void GradientLine::AddColor(Color color, double position) {
  colors_.push_back(color);
  color_positions_.push_back(position);
}

void GradientLine::ChangeColor(size_t index, Color color) {
  colors_.at(index) = color;
}

void GradientLine::Step(double proportion) {
  for (size_t i = 0; i < color_positions_.size(); i++) {
    color_positions_[i] += proportion;
    if (color_positions_[i] > 2) {
      color_positions_[i] -= 2;
    }
  }
}

Color GradientLine::GetColorAtPosition(double position) {
  if (colors_.size() == 1) {
    return colors_[0];
  }
  if (position > 2) {
    position = 2;
  }
  if (position < 0) {
    position = 0;
  }

  SortColors();

  // Gets the new position to use from te scaled function
  double pos = ScaledLineFunction(position);

  // Find the colors above and below this color and the distances separating them
  Color lower;
  Color upper;

  double color_dist;
  double dist_from_left;

  if (pos < color_positions_[0] || pos > color_positions_[color_positions_.size() - 1]) {

    color_dist = 1 - color_positions_[color_positions_.size() - 1] + color_positions_[0];
    lower = colors_[colors_.size() - 1];
    upper = colors_[0];

    if (pos < color_positions_[0]) {
      dist_from_left = 1 - color_positions_[color_positions_.size() - 1] + pos;
    } else {
      dist_from_left = pos - color_positions_[color_positions_.size() - 1];
    }
  } else {
    for (size_t i = 0; i < colors_.size() - 1; i++) {
      if (color_positions_[i] == pos) {
        return colors_[i];
      }
      if (color_positions_[i] < pos) {
        lower = colors_[i];
        upper = colors_[i + 1];
        dist_from_left = pos - color_positions_[i];
        color_dist = color_positions_[i + 1] - color_positions_[i];
      }
    }
  }

  // Interpolates based on the upper and lower colors and the distances
  double upper_proportion = dist_from_left / color_dist;
  double lower_proportion = 1 - upper_proportion;

  double red = lower.r * lower_proportion + upper.r * upper_proportion;
  double green = lower.g * lower_proportion + upper.g * upper_proportion;
  double blue = lower.b * lower_proportion + upper.b * upper_proportion;

  return Color(red, green, blue);

}

double GradientLine::ScaledLineFunction(double x) const {
  double scaled_input = x * (function_domain_[1] - function_domain_[0]) + function_domain_[0];
  double output = LineFunction(function_, scaled_input);
  double scaled_output = (output - function_range_[0]) / (function_range_[1] - function_range_[0]);
  return scaled_output;
}

double GradientLine::LineFunction(line_function func, double x) const {
  switch (func) {
    case Line:
      return x;
    case Sine:
      return sin(x);
    case Cosine:
      return cos(x);
    case Square:
      return x * x;
    case Quad:
      return x * x * x * x;
    case Sqrt:
      return sqrt(x);
  }
}

vec2 GradientLine::ApproximateFunctionRange(line_function func, vec2 domain) {
  double min = std::numeric_limits<double>::max();
  double max = std::numeric_limits<double>::min();

  for (double x = domain[0]; x < domain[1]; x += kFuncApproximationConst) {
    double value = LineFunction(func, x);
    if (value < min) {
      min = value;
    }
    if (value > max) {
      max = value;
    }
  }

  return vec2(min, max);
}

void GradientLine::SortColors() {
  for (size_t i = 0; i < color_positions_.size() - 1; i++) {
    size_t smallest_index = i;
    for (size_t j = i + 1; j < color_positions_.size(); j++) {
      if (color_positions_[j] < color_positions_[smallest_index]) {
        smallest_index = j;
      }
    }

    if (i != smallest_index) {
      Color temp_color = colors_[i];
      colors_[i] = colors_[smallest_index];
      colors_[smallest_index] = temp_color;

      double temp_color_pos = color_positions_[i];
      color_positions_[i] = color_positions_[smallest_index];
      color_positions_[smallest_index] = temp_color_pos;
    }
  }
}

}

}