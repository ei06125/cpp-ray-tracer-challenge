// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

SCENARIO("The default material")
{
  GIVEN("m = material()")
  {
    auto m = Material();

    THEN("m.color == color(1, 1, 1) &&\
        \n m.ambient == 0.1 &&\
        \n m.diffuse == 0.9 &&\
        \n m.specular = 0.9 &&\
        \n m.shininess = 200.0")
    {
      CHECK(m.color == make_color(1, 1, 1));
      CHECK(m.ambient == doctest::Approx(0.1));
      CHECK(m.diffuse == doctest::Approx(0.9));
      CHECK(m.specular == doctest::Approx(0.9));
      CHECK(m.shininess == doctest::Approx(200.0));
    }
  }
}

SCENARIO("Lighting with the eye between the light and the surface")
{
  GIVEN("m = material() && position = point(0, 0, 0) &&\
    \n eyev = vector(0, 0, -1) &&\
    \n normalv = vector(0, 0, -1) &&\
    \n light = point_light(point(0, 0, -10), color(1, 1, 1))")
  {
    auto m = Material();
    auto position = make_point(0, 0, 0);
    auto eyev = make_vector(0, 0, -1);
    auto normalv = make_vector(0, 0, -1);
    auto light = PointLight{ make_point(0, 0, -10), make_color(1, 1, 1) };

    WHEN("result = lighting(m, light, position, eyev, normalv)")
    {
      auto result = lighting(m, light, position, eyev, normalv);

      THEN("result == color(1.9, 1.9, 1.9)")
      {
        CHECK(result == make_color(1.9, 1.9, 1.9));
      }
    }
  }
}

SCENARIO("Lighting with the eye between light and surface, eye offset 45")
{
  GIVEN("m = material() && position = point(0, 0, 0) &&\
    \n eyev = vector(0, SQRT(2)/2, -SQRT(2)/2) &&\
    \n normalv = vector(0, 0, -1) &&\
    \n light = point_light(point(0, 0, -10), color(1, 1, 1))")
  {
    auto m = Material();
    auto position = make_point(0, 0, 0);
    auto eyev = make_vector(0, std::sqrt(2) / 2, -std::sqrt(2) / 2);
    auto normalv = make_vector(0, 0, -1);
    auto light = PointLight{ make_point(0, 0, -10), make_color(1, 1, 1) };

    WHEN("result = lighting(m, light, position, eyev, normalv)")
    {
      auto result = lighting(m, light, position, eyev, normalv);

      THEN("result == color(1.0, 1.0, 1.0)")
      {
        CHECK(result == make_color(1.0, 1.0, 1.0));
      }
    }
  }
}

SCENARIO("Lighting with the eye opposite surface, light offset 45")
{
  GIVEN("m = material() && position = point(0, 0, 0) &&\
    \n eyev = vector(0, 0, -1) &&\
    \n normalv = vector(0, 0, -1) &&\
    \n light = point_light(point(0, 10, -10), color(1, 1, 1))")
  {
    auto m = Material();
    auto position = make_point(0, 0, 0);
    auto eyev = make_vector(0, 0, -1);
    auto normalv = make_vector(0, 0, -1);
    auto light = PointLight{ make_point(0, 10, -10), make_color(1, 1, 1) };

    WHEN("result = lighting(m, light, position, eyev, normalv)")
    {
      auto result = lighting(m, light, position, eyev, normalv);

      THEN("result == color(0.7364, 0.7364, 0.7364)")
      {
        CHECK(result == make_color(0.7364, 0.7364, 0.7364));
      }
    }
  }
}

SCENARIO("Lighting with the eye in the path of the reflection vector")
{
  GIVEN("m = material() && position = point(0, 0, 0) &&\
    \n eyev = vector(0, -SQRT(2)/2, -SQRT(2)/2) &&\
    \n normalv = vector(0, 0, -1) &&\
    \n light = point_light(point(0, 10, -10), color(1, 1, 1))")
  {
    auto m = Material();
    auto position = make_point(0, 0, 0);
    auto eyev = make_vector(0, -std::sqrt(2) / 2, -std::sqrt(2) / 2);
    auto normalv = make_vector(0, 0, -1);
    auto light = PointLight{ make_point(0, 10, -10), make_color(1, 1, 1) };

    WHEN("result = lighting(m, light, position, eyev, normalv)")
    {
      auto result = lighting(m, light, position, eyev, normalv);

      THEN("result == color(1.6364, 1.6364, 1.6364)")
      {
        CHECK(result == make_color(1.6364, 1.6364, 1.6364));
      }
    }
  }
}

SCENARIO("Lighting with the light behind the surface")
{
  GIVEN("m = material() && position = point(0, 0, 0) &&\
    \n eyev = vector(0, 0, -1) &&\
    \n normalv = vector(0, 0, -1) &&\
    \n light = point_light(point(0, 0, 10), color(1, 1, 1))")
  {
    auto m = Material();
    auto position = make_point(0, 0, 0);
    auto eyev = make_vector(0, 0, -1);
    auto normalv = make_vector(0, 0, -1);
    auto light = PointLight{ make_point(0, 0, 10), make_color(1, 1, 1) };

    WHEN("result = lighting(m, light, position, eyev, normalv)")
    {
      auto result = lighting(m, light, position, eyev, normalv);

      THEN("result == color(0.1, 0.1, 0.1)")
      {
        CHECK(result == make_color(0.1, 0.1, 0.1));
      }
    }
  }
}

/// ===========================================================================
/// @section Shadows
/// ===========================================================================

SCENARIO("Lighting with the surface in the shadow")
{
  GIVEN("m = material() && position = point(0, 0, 0) &&\
    \n eyev = vector(0, 0, -1) &&\
    \n normalv = vector(0, 0, -1) &&\
    \n light = point_light(point(0, 0, -10), color(1, 1, 1)) &&\
    \n in_shadow = true")
  {
    auto m = Material();
    auto position = make_point(0, 0, 0);
    auto eyev = make_vector(0, 0, -1);
    auto normalv = make_vector(0, 0, -1);
    auto light = PointLight{ make_point(0, 0, -10), make_color(1, 1, 1) };
    auto in_shadow = true;

    WHEN("result = lighting(m, light, position, eyev, normalv, in_shadow)")
    {
      auto result = lighting(m, light, position, eyev, normalv, in_shadow);

      THEN("result == color(0.1, 0.1, 0.1)")
      {
        CHECK(result == make_color(0.1, 0.1, 0.1));
      }
    }
  }
}
