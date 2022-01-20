// Test Framework
#include "doctest/doctest.h"

// Project Library
#include "Rendering/Canvas.hpp"

// C++ Standard Library
#include <iostream>

SCENARIO("Creating a canvas")
{
  GIVEN("c = canvas(10, 20)")
  {
    auto c = Canvas(10, 20);
    THEN("c.width == 10 && c.height == 20 &&\
          every pixel of c is color(0, 0, 0)")
    {
      CHECK(c.width == 10);
      CHECK(c.height == 20);
      REQUIRE(c.size() == 200);
      for (const auto& pixel : c) {
        CHECK(pixel == make_color(0, 0, 0));
      }
    }
  }
}

SCENARIO("Writing pixels to a canvas")
{
  GIVEN("c = canvas(10, 20) && red = color(1, 0, 0)")
  {
    auto c = Canvas(10, 20);
    auto red = make_color(1, 0, 0);
    WHEN("write_pixel(c, 2, 3, red)")
    {
      write_pixel(c, 2, 3, red);
      THEN("pixel_at(c, 2, 3) == red") { CHECK(pixel_at(c, 2, 3) == red); }
    }
  }
}

SCENARIO("Constructing the PPM header")
{
  GIVEN("c = canvas(5, 3)")
  {
    auto c = Canvas(5, 3);
    WHEN("ppm = canvas_to_ppm(c)")
    {
      auto ppm = canvas_to_ppm(c);
      THEN("lines 1-3 of ppm are:\n\
        P3\n\
        5 3\n\
        255")
      {
        std::string expected = "";
        expected += "P3\n";
        expected += "5 3\n";
        expected += "255\n";
        CHECK(ppm == expected);
      }
    }
  }
}

SCENARIO("Constructing the PPM pixel data")
{
  GIVEN("c = canvas(5, 3) &&\
    c1 = color(1.5, 0, 0) && c2 = color(0, 0.5, 0) && c3 = color(-0.5, 0, 1)")
  {
    auto c = Canvas(5, 3);
    auto c1 = make_color(1.5, 0, 0);
    auto c2 = make_color(0, 0.5, 0);
    auto c3 = make_color(-0.5, 0, 1);
    WHEN("write_pixel(c, 0, 0, c1) &&\
          write_pixel(c, 2, 1, c2) &&\
          write_pixel(c, 4, 2, c3) &&\
          ppm = canvas_to_ppm(c)")
    {
      write_pixel(c, 0, 0, c1);
      write_pixel(c, 2, 1, c2);
      write_pixel(c, 4, 2, c3);
      auto ppm = canvas_to_ppm(c);

      THEN("lines 4-6 of ppm are:\n\
      255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n\
      0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n\
      0 0 0 0 0 0 0 0 0 0 0 0 0 0 255")
      {
        std::string expected = "";
        expected += "P3\n";  // Optional ?
        expected += "5 3\n"; // Optional ?
        expected += "255\n"; // Optional ?
        expected += "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";
        expected += "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n";
        expected += "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
        expected += "\n";

        CHECK(ppm == expected);
      }
    }
  }
}

SCENARIO("Splitting long lines in PPM files")
{
  GIVEN("c = canvas(10, 2)")
  {
    auto c = Canvas(10, 2);
    WHEN("every pixel of c is set to color(1, 0.8, 0.6) &&\
          ppm = canvas_to_ppm(c)")
    {
      auto color = make_color(1, 0.8, 0.6);
      for (auto col = 0; col < 10; ++col) {
        for (auto row = 0; row < 2; ++row) {
          write_pixel(c, col, row, color);
        }
      }
      auto ppm = canvas_to_ppm(c);

      THEN("lines 4-7 of ppm are:\n\
      255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\
      153 255 204 153 255 204 153 255 204 153 255 204 153\
      255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\
      153 255 204 153 255 204 153 255 204 153 255 204 153\
      ")
      {
        ;
        std::string expected = "";
        expected += "P3\n";   // Optional ?
        expected += "10 2\n"; // Optional ?
        expected += "255\n";  // Optional ?
        expected += "255 204 153 255 204 153 255 204 153 255 204 153 255 204 "
                    "153 255 204\n";
        expected += "153 255 204 153 255 204 153 255 204 153 255 204 153\n";
        expected += "255 204 153 255 204 153 255 204 153 255 204 153 255 204 "
                    "153 255 204\n";
        expected += "153 255 204 153 255 204 153 255 204 153 255 204 153\n";
        expected += "\n";

        CHECK(ppm == expected);
      }
    }
  }
}

SCENARIO("PPM files are terminated by a newline character")
{
  GIVEN("c = canvas(5, 3)")
  {
    auto c = Canvas(5, 3);
    WHEN("ppm = canvas_to_ppm(c)")
    {
      auto ppm = canvas_to_ppm(c);
      THEN("ppm ends with a newline character")
      {
        CHECK(ppm.at(ppm.size() - 1) == '\n');
      }
    }
  }
}
