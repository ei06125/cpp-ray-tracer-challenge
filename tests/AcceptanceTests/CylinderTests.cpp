// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

using namespace RayTracer::Rendering::Primitives;
using namespace RayTracer::Math;

SCENARIO("A ray misses a cylinder")
{
  GIVEN("cyl = cylinder()\
    \n\t And direction = normalize(<direction>)\
    \n\t And r = ray(point(<origin>, direction)")
  {

    /// -----------------------------------------------------------------------
    /// @subsection Example Test Data
    struct TestData
    {
      Tuple origin;
      Tuple direction;
    };

    const std::array<TestData, 3> testData{ {
      { Point(1, 0, 0), Vector(0, 1, 0) },
      { Point(0, 0, 0), Vector(0, 1, 0) },
      { Point(0, 0, -5), Vector(1, 1, 1) },
    } };
    /// -----------------------------------------------------------------------

    auto cyl = Cylinder();
    for (const auto& [origin, direction] : testData) {
      auto r = Ray{ origin, normalize(direction) };
      WHEN("xs = local_intersect(cyl, r)")
      {
        auto xs = cyl.Intersect(r);
        THEN("xs.count == 0") { CHECK(xs.Count() == 0); }
      }
    }
  }
}

SCENARIO("A ray strikes a cylinder")
{
  GIVEN("cyl = cylinder()\
    \n\t And direction = normalize(<direction>)\
    \n\t And r = ray(point(<origin>, direction)")
  {

    /// -----------------------------------------------------------------------
    /// @subsection Example Test Data
    struct TestData
    {
      Tuple origin;
      Tuple direction;
      float t0;
      float t1;
    };

    const std::array<TestData, 3> testData{ {
      { Point(1, 0, -5), Vector(0, 0, 1), 5, 5 },
      { Point(0, 0, -5), Vector(0, 0, 1), 4, 6 },
      { Point(0.5, 0, -5), Vector(0.1, 1, 1), 6.80798, 7.08872 },
    } };
    /// -----------------------------------------------------------------------

    auto cyl = Cylinder();
    for (const auto& [origin, direction, t0, t1] : testData) {
      auto r = Ray{ origin, normalize(direction) };
      WHEN("xs = local_intersect(cyl, r)")
      {
        auto xs = cyl.Intersect(r);
        THEN("xs.count == 2 \
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

SCENARIO("Normal vector on a cylinder")
{
  GIVEN("cyl = cylinder()")
  {
    /// -----------------------------------------------------------------------
    /// @subsection Example Test Data
    struct TestData
    {
      Tuple point;
      Tuple normal;
    };

    const std::array<TestData, 4> testData{ {
      { Point(1, 0, 0), Vector(1, 0, 0) },
      { Point(0, 5, -1), Vector(0, 0, -1) },
      { Point(0, -2, 1), Vector(0, 0, 1) },
      { Point(-1, 1, 0), Vector(-1, 0, 0) },
    } };
    /// -----------------------------------------------------------------------

    auto cyl = Cylinder();
    for (const auto& [point, normal] : testData) {
      WHEN("n = local_normal_at(cyl, <point>)")
      {
        auto n = cyl.GetNormalAt(point);
        THEN("n == <normal>") { CHECK(n == normal); }
      }
    }
  }
}

SCENARIO("The default  minimum and maximum for a cylinder")
{
  GIVEN("cyl = cylinder()")
  {
    auto cyl = Cylinder();
    THEN("cyl.minimum == -infinity And cyl.maximum = infinity")
    {
      CHECK(cyl.GetMinimum() == -INFINITY);
      CHECK(cyl.GetMaximum() == INFINITY);
    }
  }
}

SCENARIO("Intersecting a constrained cylinder")
{
  GIVEN("cyl = cylinder()\
  \n\t And cyl.minimum = 1\
  \n\t And cyl.maximum = 2\
  \n\t And direction = normalize(<direction>)\
  \n\t And r = ray(point(<point>, direction)")
  {
    /// -----------------------------------------------------------------------
    /// @subsection Example Test Data
    struct TestData
    {
      Tuple point;
      Tuple direction;
      std::size_t count;
    };

    const std::array<TestData, 6> testData{
      { { Point(0, 1.5, 0), Vector(0.1, 1, 0), 0 },
        { Point(0, 3, -5), Vector(0, 0, 1), 0 },
        { Point(0, 0, -5), Vector(0, 0, 1), 0 },
        { Point(0, 2, -5), Vector(0, 0, 1), 0 },
        { Point(0, 1, -5), Vector(0, 0, 1), 0 },
        { Point(0, 1.5, -2), Vector(0, 0, 1), 2 } }
    };
    /// -----------------------------------------------------------------------

    auto cyl = Cylinder();
    cyl.SetMinimum(1);
    cyl.SetMaximum(2);
    for (const auto& [point, direction, count] : testData) {
      auto r = Ray{ point, normalize(direction) };
      WHEN("xs = local_intersect(cyl, r)")
      {
        auto xs = cyl.Intersect(r);
        THEN("xs.count == <count>")
        {
          INFO("point:", point);
          CHECK(xs.Count() == count);
        }
      }
    }
  }
}

SCENARIO("The default closed value for a cylinder")
{
  GIVEN("cyl = cylinder()")
  {
    auto cyl = Cylinder();
    THEN("cyl.closed == false") { CHECK(cyl.IsClosed() == false); }
  }
}

SCENARIO("Intersecting the caps of a closed cylinder")
{
  GIVEN("cyl = cylinder()\
  \n\t And cyl.minimum = 1\
  \n\t And cyl.maximum = 2\
  \n\t And cyl.closed = true\
  \n\t And direction = normalize(<direction>)\
  \n\t And r = ray(point(<point>, direction)")
  {
    /// -----------------------------------------------------------------------
    /// @subsection Example Test Data
    struct TestData
    {
      Tuple point;
      Tuple direction;
      std::size_t count;
    };

    const std::array<TestData, 5> testData{ {
      { Point(0, 3, 0), Vector(0, -1, 0), 2 },
      { Point(0, 3, -2), Vector(0, -1, 2), 2 },
      { Point(0, 4, -2), Vector(0, -1, 1), 2 }, // corner case
      { Point(0, 0, -2), Vector(0, 1, 2), 2 },
      { Point(0, -1, -2), Vector(0, 1, 1), 2 }, // corner case
    } };
    /// -----------------------------------------------------------------------

    auto cyl = Cylinder();
    cyl.SetMinimum(1);
    cyl.SetMaximum(2);
    cyl.SetClosed(true);
    for (const auto& [point, direction, count] : testData) {
      auto r = Ray{ point, normalize(direction) };
      WHEN("xs = local_intersect(cyl, r)")
      {
        auto xs = cyl.Intersect(r);
        THEN("xs.count == <count>")
        {
          INFO("point:", point);
          CHECK(xs.Count() == count);
        }
      }
    }
  }
}

SCENARIO("The normal vector on a cylinder's end caps")
{
  GIVEN("cyl = cylinder()\
  \n\t And cyl.minimum = 1\
  \n\t And cyl.maximum = 2\
  \n\t And cyl.closed = true")
  {
    /// -----------------------------------------------------------------------
    /// @subsection Example Test Data
    struct TestData
    {
      Tuple point;
      Tuple normal;
    };

    const std::array<TestData, 6> testData{ {
      { Point(0, 1, 0), Vector(0, -1, 0) },
      { Point(0.5, 1, 0), Vector(0, -1, 0) },
      { Point(0, 1, 0.5), Vector(0, -1, 0) },
      { Point(0, 2, 0), Vector(0, 1, 0) },
      { Point(0.5, 2, 0), Vector(0, 1, 0) },
      { Point(0, 2, 0.5), Vector(0, 1, 0) },
    } };
    /// -----------------------------------------------------------------------

    auto cyl = Cylinder();
    cyl.SetMinimum(1);
    cyl.SetMaximum(2);
    cyl.SetClosed(true);
    for (const auto& [point, normal] : testData) {
      WHEN("n = local_normal_at(cyl, <point>)")
      {
        auto n = cyl.GetNormalAt(point);

        THEN("n == <normal>") { CHECK(n == normal); }
      }
    }
  }
}
