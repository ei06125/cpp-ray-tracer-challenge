// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

using namespace RayTracer::Rendering::Primitives;
using namespace RayTracer::Math;

SCENARIO("Intersecting a cone with a ray")
{
  GIVEN("shape = cone()\
    \n\t And direction = normalize(<direction>)\
    \n\t And r = ray(<point>, direction)")
  {
    /// -----------------------------------------------------------------------
    /// @subsection Example Test Data
    struct TestData
    {
      Tuple point;
      Tuple direction;
      float t0;
      float t1;
    };

    const std::array<TestData, 3> testData{ {
      { Point(0, 0, -5), Vector(0, 0, 1), 5, 5 },
      { Point(0, 0, -5), Vector(1, 1, 1), 8.66025, 8.66025 },
      { Point(1, 1, -5), Vector(-0.5, -1, 1), 4.55006, 49.44994 },
    } };
    /// -----------------------------------------------------------------------

    auto shape = Cone();
    for (const auto& [point, direction, t0, t1] : testData) {
      auto r = Ray{ point, normalize(direction) };
      WHEN("xs = local_intersect(shape, r)")
      {
        auto xs = shape.Intersect(r);

        THEN("xs.count == 2\
            \n\t And xs[0].t == <t0>\
            \n\t And xs[1].t == <t1>")
        {
          CHECK(xs.Count() == 2);
          CHECK(xs[0].t == t0);
          CHECK(xs[1].t == t1);
        }
      }
    }
  }
}

SCENARIO("Intersecting a cone with a ray parallel to one of its halves")
{
  GIVEN("shape = cone()\
    \n\t And direction = normalize(vector(0, 1, 1))\
    \n\t And r = ray(point(0, 0, -1), direction)")
  {
    auto shape = Cone();
    auto direction = normalize(Vector(0, 1, 1));
    auto r = Ray{ Point(0, 0, -1), direction };

    WHEN("xs = local_intersect(shape, r)")
    {
      auto xs = shape.Intersect(r);

      THEN("xs.count == 1\
        \n\t And xs[0].t == 0.35355")
      {
        CHECK(xs.Count() == 1);
        CHECK(xs[0].t == doctest::Approx(0.35355));
      }
    }
  }
}

SCENARIO("Intersecting a cone's end caps")
{
  GIVEN("shape = cone()\
  \n\t And shape.minimum = -0.5\
  \n\t And shape.maximum = 0.5\
  \n\t And shape.closed = true\
  \n\t And direction = normalize(<direction>)\
  \n\t And r = ray(<origin>, direction)")
  {
    /// -----------------------------------------------------------------------
    /// @subsection Example Test Data
    struct TestData
    {
      Tuple origin;
      Tuple direction;
      std::size_t count;
    };

    const std::array<TestData, 3> testData{ {
      { Point(0, 0, -5), Vector(0, 1, 0), 0 },
      { Point(0, 0, -0.25), Vector(0, 1, 1), 2 },
      { Point(0, 0, -0.25), Vector(0, 1, 0), 4 },
    } };
    /// -----------------------------------------------------------------------

    auto shape = Cone();
    shape.SetMinimum(-0.5);
    shape.SetMaximum(0.5);
    shape.SetClosed(true);
    for (const auto& [origin, direction, count] : testData) {
      auto r = Ray{ origin, normalize(direction) };
      WHEN("xs = local_intersect(shape, r)")
      {
        auto xs = shape.Intersect(r);
        THEN("xs.count == <count>") { CHECK(xs.Count() == count); }
      }
    }
  }
}

SCENARIO("Computing the normal vector on a cone")
{
  GIVEN("shape = cone()")
  {
    /// -----------------------------------------------------------------------
    /// @subsection Example Test Data
    struct TestData
    {
      Tuple point;
      Tuple normal;
    };

    const std::array<TestData, 3> testData{ {
      { Point(0, 0, 0), Vector(0, 0, 0) },
      { Point(1, 1, 1), Vector(1, -std::sqrt(2), 1) },
      { Point(-1, -1, 0), Vector(-1, 1, 0) },
    } };
    /// -----------------------------------------------------------------------

    auto shape = Cone();
    for (const auto& [point, normal] : testData) {
      WHEN("n = local_normal_at(shape, <point>)")
      {
        auto n = shape.TestLocalNormalAt(point);
        THEN("n == <normal>") { CHECK(n == normal); }
      }
    }
  }
}
