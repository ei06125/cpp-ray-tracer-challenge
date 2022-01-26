// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

using namespace RayTracer::Math;
using namespace RayTracer::Rendering::Cameras;

SCENARIO("Constructing a camera")
{
  GIVEN("hsize = 160 && vsize = 120 && field_of_view = PI/2")
  {
    auto hsize = 160.0f;
    auto vsize = 120.0f;
    auto fov = PI / 2;

    WHEN("c = camera(hsize, vsize, field_of_view)")
    {
      auto c = Camera{ hsize, vsize, fov };

      THEN("c.hsize == 160 &&\
      \n c.vsize == 120 &&\
      \n c.field_of_view = PI/2 &&\
      \n c.transform == identity_matrix")
      {
        CHECK(c.hsize == 160);
        CHECK(c.vsize == 120);
        CHECK(c.field_of_view == PI / 2);
        CHECK(c.transform == mat4::Identity());
      }
    }
  }
}

SCENARIO("The pixel size for a horizontal canvas")
{
  GIVEN("c = camera(200, 125, PI/2)")
  {
    auto c = Camera{ 200, 125, PI / 2 };

    THEN("c.pixel_size == 0.01") { CHECK(c.pixel_size == 0.01f); }
  }
}

SCENARIO("The pixel size for a vertical canvas")
{
  GIVEN("c = camera(125, 200, PI/2)")
  {
    auto c = Camera{ 125, 200, PI / 2 };

    THEN("c.pixel_size == 0.01") { CHECK(c.pixel_size == 0.01f); }
  }
}

SCENARIO("Constructing a ray through the center of the canvas")
{
  GIVEN("c = camera(201, 101, PI/2)")
  {
    auto c = Camera{ 201, 101, PI / 2 };

    WHEN("r = ray_for_pixel(c, 100, 50)")
    {
      auto r = ray_for_pixel(c, 100, 50);

      THEN("r.origin == point(0, 0, 0) &&\
      \n r.direction == vector(0, 0, -1)")
      {
        CHECK(r.origin == make_point(0, 0, 0));
        CHECK(r.direction == make_vector(0, 0, -1));
      }
    }
  }
}

SCENARIO("Constructing a ray through a corner of the canvas")
{
  GIVEN("c = camera(201, 101, PI/2)")
  {
    auto c = Camera{ 201, 101, PI / 2 };

    WHEN("r = ray_for_pixel(c, 0, 0)")
    {
      auto r = ray_for_pixel(c, 0, 0);

      THEN("r.origin == point(0, 0, 0) &&\
      \n r.direction == vector(0.66519, 0.33259, -0.66851)")
      {
        CHECK(r.origin == make_point(0, 0, 0));
        CHECK(r.direction == make_vector(0.66519, 0.33259, -0.66851));
      }
    }
  }
}

SCENARIO("Constructing a ray when the camera is transformed")
{
  GIVEN("c = camera(201, 101, PI/2)")
  {
    auto c = Camera{ 201, 101, PI / 2 };

    WHEN("c.transform = rotation_y(PI/4) * translation(0, -2, 5) &&\
    \n r = ray_for_pixel(c, 100, 50)")
    {
      c.transform = rotation_y(PI / 4) * translation(0, -2, 5);
      auto r = ray_for_pixel(c, 100, 50);

      THEN("r.origin == point(0, 2, -5) &&\
      \n r.direction == vector(SQRT(2)/2, 0, -SQRT(2)/2)")
      {
        CHECK(r.origin == make_point(0, 2, -5));
        CHECK(r.direction ==
              make_vector(std::sqrt(2) / 2, 0, -std::sqrt(2) / 2));
      }
    }
  }
}

SCENARIO("Rendering a world with a camera")
{
  GIVEN("w = default_world() &&\
    \n c = camera(11, 11, PI/2) &&\
    \n from = point(0, 0, -5) &&\
    \n to = point(0, 0, 0) &&\
    \n up = vector(0, 1, 0) &&\
    \n c.transform = view_transform(from, to, up)")
  {
    auto w = default_world();
    auto c = Camera{ 11, 11, PI / 2 };
    auto from = make_point(0, 0, -5);
    auto to = make_point(0, 0, 0);
    auto up = make_vector(0, 1, 0);
    c.transform = view_transform(from, to, up);

    WHEN("image = render(c, w)")
    {
      auto image = render(c, w);

      THEN("pixel_at(image, 5, 5) == color(0.38066, 0.47583, 0.2855)")
      {
        CHECK(pixel_at(image, 5, 5) == make_color(0.38066, 0.47583, 0.2855));
      }
    }
  }
}
