// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

using namespace RayTracer::Math;
using namespace RayTracer::Rendering::Lighting;

SCENARIO("A point light has a position and intensity")
{
  GIVEN("intensity = color(1, 1, 1) && position = point(0, 0, 0)")
  {
    auto intensity = Color{ 1.0f, 1.0f, 1.0f };
    auto position = Point(0, 0, 0);

    WHEN("light = point_light(position, intensity)")
    {
      auto light = PointLight{ position, intensity };

      THEN("light.position == position && light.intensity == intensity")
      {
        CHECK(light.position == position);
        CHECK(light.intensity == intensity);
      }
    }
  }
}
