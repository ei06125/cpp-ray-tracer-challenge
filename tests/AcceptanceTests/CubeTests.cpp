// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

using namespace RayTracer::Rendering::Primitives;
using namespace RayTracer::Math;

SCENARIO("A ray intersects a cube")
{
  GIVEN("c = cube() And r = ray(<origin>, <direction>")
  {

    /// -----------------------------------------------------------------------
    /// @subsection Example Test Data
    struct TestData
    {
      Tuple origin;
      Tuple direction;
      float t1;
      float t2;
    };

    const std::array<TestData, 7> testData{ {
      { Point(5, 0.5, 0), Vector(-1, 0, 0), 4, 6 },
      { Point(-5, 0.5, 0), Vector(1, 0, 0), 4, 6 },
      { Point(0.5, 5, 0), Vector(0, -1, 0), 4, 6 },
      { Point(0.5, -5, 0), Vector(0, 1, 0), 4, 6 },
      { Point(0.5, 0, 5), Vector(0, 0, -1), 4, 6 },
      { Point(0.5, 0, -5), Vector(0, 0, 1), 4, 6 },
      { Point(0, 0.5, 0), Vector(0, 0, 1), -1, 1 },
    } };
    /// -----------------------------------------------------------------------

    auto c = Cube();
    for (const auto& [origin, direction, t1, t2] : testData) {
      auto r = Ray{ origin, direction };
      WHEN("xs = local_intersect(c, r)")
      {
        auto xs = c.Intersect(r);
        THEN("xs.count == 2\
            \n\t And xs[0].t = <t1>\
            \n\t And xs[1].t = <t2>")
        {
          CHECK(xs.Count() == 2);
          CHECK(xs[0].t == t1);
          CHECK(xs[1].t == t2);
        }
      }
    }
  }
}

SCENARIO("A ray misses a cube")
{
  GIVEN("c = cube() And r = ray(<origin>, <direction>")
  {

    /// -----------------------------------------------------------------------
    /// @subsection Example Test Data
    struct TestData
    {
      Tuple origin;
      Tuple direction;
    };

    const std::array<TestData, 6> testData{ {
      { Point(-2, 0, 0), Vector(0.2673, 0.5345, 0.8018) },
      { Point(0, -2, 0), Vector(0.8018, 0.2673, 0.5345) },
      { Point(0, 0, -2), Vector(0.5345, 0.8018, 0.2673) },
      { Point(2, 0, 2), Vector(0, 0, -1) },
      { Point(0, 2, 2), Vector(0, -1, 0) },
      { Point(2, 2, 0), Vector(-1, 0, 0) },
    } };
    /// -----------------------------------------------------------------------

    auto c = Cube();
    for (const auto& [origin, direction] : testData) {
      auto r = Ray{ origin, direction };
      WHEN("xs = local_intersect(c, r)")
      {
        auto xs = c.Intersect(r);

        THEN("xs.count == 0") { CHECK(xs.Count() == 0); }
      }
    }
  }
}

SCENARIO("The normal on the surface of a cube")
{
  GIVEN("c = cube() And p = <point>")
  {

    /// -----------------------------------------------------------------------
    /// @subsection Example Test Data
    struct TestData
    {
      Tuple point;
      Tuple normal;
    };

    const std::array<TestData, 8> testData{ {
      { Point(1, 0.5, -0.8), Vector(1, 0, 0) },
      { Point(-1, -0.2, 0.9), Vector(-1, 0, 0) },
      { Point(-0.4, 1, -0.1), Vector(0, 1, 0) },
      { Point(0.3, -1, -0.7), Vector(0, -1, 0) },
      { Point(-0.6, 0.3, 1), Vector(0, 0, 1) },
      { Point(0.4, 0.4, -1), Vector(0, 0, -1) },
      { Point(1, 1, 1), Vector(1, 0, 0) },
      { Point(-1, -1, -1), Vector(-1, 0, 0) },
    } };
    /// -----------------------------------------------------------------------

    auto c = Cube();
    for (const auto& [point, normal] : testData) {
      auto p = point;
      WHEN("normal = local_normal_at(c, p)")
      {
        auto n = c.GetNormalAt(p);

        THEN("normal == <normal>") { CHECK(n == normal); }
      }
    }
  }
}
