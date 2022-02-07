// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

using namespace RayTracer::Math;
using namespace RayTracer::Rendering::Colors;
using namespace RayTracer::Rendering::Patterns;
using namespace RayTracer::Rendering::Materials;

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
      CHECK(m.color == Color{ 1.0f, 1.0f, 1.0f });
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
    auto position = Point(0, 0, 0);
    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight{ Point(0, 0, -10), Color{ 1.0f, 1.0f, 1.0f } };

    WHEN("result = lighting(m, light, position, eyev, normalv)")
    {
      auto result = lighting(m, light, position, eyev, normalv);

      THEN("result == color(1.9, 1.9, 1.9)")
      {
        CHECK(result == Color{ 1.9f, 1.9f, 1.9f });
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
    auto position = Point(0, 0, 0);
    auto eyev = Vector(0, std::sqrt(2) / 2, -std::sqrt(2) / 2);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight{ Point(0, 0, -10), Color{ 1.0f, 1.0f, 1.0f } };

    WHEN("result = lighting(m, light, position, eyev, normalv)")
    {
      auto result = lighting(m, light, position, eyev, normalv);

      THEN("result == color(1.0, 1.0, 1.0)")
      {
        CHECK(result == Color{ 1.0f, 1.0f, 1.0f });
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
    auto position = Point(0, 0, 0);
    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight{ Point(0, 10, -10), Color{ 1.0f, 1.0f, 1.0f } };

    WHEN("result = lighting(m, light, position, eyev, normalv)")
    {
      auto result = lighting(m, light, position, eyev, normalv);

      THEN("result == color(0.7364, 0.7364, 0.7364)")
      {
        CHECK(result == Color{ 0.7364f, 0.7364f, 0.7364f });
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
    auto position = Point(0, 0, 0);
    auto eyev = Vector(0, -std::sqrt(2) / 2, -std::sqrt(2) / 2);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight{ Point(0, 10, -10), Color{ 1.0f, 1.0f, 1.0f } };

    WHEN("result = lighting(m, light, position, eyev, normalv)")
    {
      auto result = lighting(m, light, position, eyev, normalv);

      THEN("result == color(1.6364, 1.6364, 1.6364)")
      {
        CHECK(result == Color{ 1.6364f, 1.6364f, 1.6364f });
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
    auto position = Point(0, 0, 0);
    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight{ Point(0, 0, 10), Color{ 1.0f, 1.0f, 1.0f } };

    WHEN("result = lighting(m, light, position, eyev, normalv)")
    {
      auto result = lighting(m, light, position, eyev, normalv);

      THEN("result == color(0.1, 0.1, 0.1)")
      {
        CHECK(result == Color{ 0.1f, 0.1f, 0.1f });
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
    auto position = Point(0, 0, 0);
    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);
    auto light = PointLight{ Point(0, 0, -10), Color{ 1.0f, 1.0f, 1.0f } };
    auto in_shadow = true;

    WHEN("result = lighting(m, light, position, eyev, normalv, in_shadow)")
    {
      auto result = lighting(m, light, position, eyev, normalv, in_shadow);

      THEN("result == color(0.1, 0.1, 0.1)")
      {
        CHECK(result == Color{ 0.1f, 0.1f, 0.1f });
      }
    }
  }
}

/// ===========================================================================
/// @section Patterns
/// ===========================================================================

SCENARIO("Lighting with a pattern applied")
{
  GIVEN("m.pattern = stripe_pattern(color(1, 1, 1), color(0, 0, 0)) &&\
  \n m.ambient = 1 && m.diffuse = 0 && m.specular = 0 &&\
  \n eyev = vector(0, 0, -1) && normalv = vector(0, 0, -1) &&\
  \n light = point_light(point(0, 0, -10), color(1, 1, 1))")
  {
    auto pattern = std::make_shared<StripePattern>(Color{ 1.0f, 1.0f, 1.0f },
                                                   Color{ 0.0f, 0.0f, 0.0f });
    Material m;
    m.pattern = std::static_pointer_cast<Pattern>(pattern);
    m.ambient = 1;
    m.diffuse = 0;
    m.specular = 0;

    auto eyev = Vector(0, 0, -1);
    auto normalv = Vector(0, 0, -1);

    auto light = PointLight{ Point(0, 0, -10), Color{ 1.0f, 1.0f, 1.0f } };

    WHEN("c1 = lighting(m, light, point(0.9, 0, 0), eyev, normalv, false) &&\
  \n c2 = lighting(m, light, point(1.1, 0, 0), eyev, normalv, false)")
    {

      auto c1 = lighting(m, light, Point(0.9, 0, 0), eyev, normalv, false);
      auto c2 = lighting(m, light, Point(1.1, 0, 0), eyev, normalv, false);

      THEN("c1 == color(1, 1, 1) && c2 == color(0, 0, 0)")
      {
        CHECK(c1 == Color{ 1.0f, 1.0f, 1.0f });
        CHECK(c2 == Color{ 0.0f, 0.0f, 0.0f });
      }
    }
  }
}

/// ===========================================================================
/// @section Reflection
/// ===========================================================================

SCENARIO("Reflectivity for the default material")
{
  GIVEN("m = material()")
  {
    auto m = Material();

    THEN("m.reflective = 0.0") { CHECK(m.reflective == 0.0); }
  }
}

/// ===========================================================================
/// @section Refraction
/// ===========================================================================

SCENARIO("Transparency and Refractive Index for the default material")
{
  GIVEN("m = material()")
  {
    auto m = Material();

    THEN("m.transparency == 0.0 && m.refractive_index == 1.0")
    {
      CHECK(m.transparency == 0.0);
      CHECK(m.refractiveIndex == 1.0);
    }
  }
}
