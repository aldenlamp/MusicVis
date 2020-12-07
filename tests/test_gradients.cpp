//
// Created by alden lamp on 12/4/20.
//

#include <catch2/catch.hpp>
#include <visualizer/gradient_line.h>

#include "cinder/gl/gl.h"

/*
 * Testing Strategy
 * Interpolation works:
 *   One color, Two colors, Three colors, Different positions
 * Function Interpolation:
 *   Two colors, Three Colors;
 * Step:
 *   Works
 */

using visualizer::gradient::GradientLine;
using glm::vec2;
using ci::Color;
using std::vector;

bool AreClose(Color a, Color b){
    double allowed_dist = 0.05;
    return  !(abs(a.r - b.r) > allowed_dist || abs(a.g - b.g) > allowed_dist || abs(a.b - b.b) > allowed_dist);
}

TEST_CASE("Interpolation works"){
  SECTION("One Color"){
      vector<Color> single_color = vector<Color>();
      single_color.push_back(Color("Green"));
      GradientLine grad = GradientLine(single_color);
      REQUIRE(grad.GetColorAtPosition(0.1) == Color("Green"));
      REQUIRE(grad.GetColorAtPosition(0.9) == Color("Green"));
      REQUIRE(grad.GetColorAtPosition(0.2) == Color("Green"));
  }

  SECTION("Two Color"){
        vector<Color> single_color = vector<Color>();
        single_color.push_back(Color(1,0, 0));
        single_color.push_back(Color(0.2,0, 1));
        GradientLine grad = GradientLine(single_color);

        REQUIRE(AreClose(grad.GetColorAtPosition(0.25), Color(0.6, 0, 0.5)));
        REQUIRE(AreClose(grad.GetColorAtPosition(0.75), Color(0.6, 0, 0.5)));
  }

  SECTION("Four Color"){
        vector<Color> single_color = vector<Color>();
        single_color.push_back(Color(1,0, 0));
        single_color.push_back(Color(0.2,0, 1));
        single_color.push_back(Color(0.4,0.6, 0.8));
        single_color.push_back(Color(0.2,0.6, 1));
        GradientLine grad = GradientLine(single_color);

        REQUIRE(AreClose(grad.GetColorAtPosition(0.125), Color(0.6, 0, 0.5)));
        REQUIRE(AreClose(grad.GetColorAtPosition(0.375), Color(0.3, 0.3, 0.9)));
        REQUIRE(AreClose(grad.GetColorAtPosition(0.625), Color(0.3, 0.6, 0.9)));
        REQUIRE(AreClose(grad.GetColorAtPosition(0.875), Color(0.6, 0.3, 0.5)));
  }

  SECTION("Different positions"){
        vector<Color> single_color = vector<Color>();
        single_color.push_back(Color(1,0, 0));
        single_color.push_back(Color(0.2,0, 1));
        single_color.push_back(Color(0.4,0.6, 0.8));

        vector<double> pos = vector<double>();
        pos.push_back(0.0);
        pos.push_back(0.25);
        pos.push_back(0.75);

        GradientLine grad = GradientLine(single_color, pos);

        REQUIRE(AreClose(grad.GetColorAtPosition(0.125), Color(0.6, 0, 0.5)));
        REQUIRE(AreClose(grad.GetColorAtPosition(0.5), Color(0.3, 0.3, 0.9)));
        REQUIRE(AreClose(grad.GetColorAtPosition(0.875), Color(0.7, 0.3, 0.4)));
  }
}

TEST_CASE("Function Interpolation"){
    SECTION("Two Color"){
        vector<Color> single_color = vector<Color>();
        single_color.push_back(Color(1,0, 0));
        single_color.push_back(Color(0.2,0, 1));

        GradientLine grad = GradientLine(single_color, visualizer::gradient::line_function::Sine, vec2(0, 3.1415));

        REQUIRE(AreClose(grad.GetColorAtPosition(0.242), Color(0.6, 0, 0.5)));
        REQUIRE(AreClose(grad.GetColorAtPosition(0.848), Color(0.6, 0, 0.5)));
    }
}

TEST_CASE("Step Function"){
    SECTION("Successful"){
        vector<Color> single_color = vector<Color>();
        single_color.push_back(Color(1,0, 0));
        single_color.push_back(Color(0.2,0, 1));
        single_color.push_back(Color(0.4,0.6, 0.8));

        vector<double> pos = vector<double>();
        pos.push_back(0.0);
        pos.push_back(0.25);
        pos.push_back(0.75);

        GradientLine grad = GradientLine(single_color, pos);

        REQUIRE(AreClose(grad.GetColorAtPosition(0.125), Color(0.6, 0, 0.5)));
        REQUIRE(AreClose(grad.GetColorAtPosition(0.5), Color(0.3, 0.3, 0.9)));
        REQUIRE(AreClose(grad.GetColorAtPosition(0.875), Color(0.7, 0.3, 0.4)));

        grad.Step(0.1);

        REQUIRE(AreClose(grad.GetColorAtPosition(0.225), Color(0.6, 0, 0.5)));
        REQUIRE(AreClose(grad.GetColorAtPosition(0.6), Color(0.3, 0.3, 0.9)));
        REQUIRE(AreClose(grad.GetColorAtPosition(0.975), Color(0.7, 0.3, 0.4)));

        grad.Step(0.2);

        REQUIRE(AreClose(grad.GetColorAtPosition(0.425), Color(0.6, 0, 0.5)));
        REQUIRE(AreClose(grad.GetColorAtPosition(0.8), Color(0.3, 0.3, 0.9)));
        REQUIRE(AreClose(grad.GetColorAtPosition(0.175), Color(0.7, 0.3, 0.4)));
    }
}



