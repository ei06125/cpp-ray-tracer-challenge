// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

using namespace RayTracer::Math;
using namespace RayTracer::Rendering::Primitives;

SCENARIO("Constructing a triangle")
{
  GIVEN("p1 = point(0, 1, 0)\
    \n\t And p2 = point(-1, 0, 0)\
    \n\t And p3 = point(1, 0, 0)\
    \n\t And t = triangle(p1, p2, p3)")
  {
    const auto p1 = Point(0, 1, 0);
    const auto p2 = Point(-1, 0, 0);
    const auto p3 = Point(1, 0, 0);
    auto t = Triangle(p1, p2, p3);

    THEN("t.p1 == p1\
        \n\t And t.p2 == p2\
        \n\t And t.p3 == p3\
        \n\t And t.e1 == vector(-1, -1, 0)\
        \n\t And t.e2 == vector(1, -1, 0)\
        \n\t And t.normal == vector(0, 0, -1)")
    {
      CHECK(t.p1 == p1);
      CHECK(t.p2 == p2);
      CHECK(t.p3 == p3);
      CHECK(t.e1 == Vector(-1, -1, 0));
      CHECK(t.e2 == Vector(1, -1, 0));
      CHECK(t.normal == Vector(0, 0, -1));
    }
  }
}

SCENARIO("Finding the normal on a triangle")
{
  GIVEN("t = triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0))")
  {
    auto t = Triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));

    WHEN("n1 = local_normal_at(t, point(0, 0.5, 0))\
    \n\t And n2 = local_normal_at(t, point(-0.5, 0.75, 0))\
    \n\t And n3 = local_normal_at(t, point(0.5, 0.25, 0))")
    {
      auto n1 = t.GetNormalAt(Point(0, 0.5, 0));
      auto n2 = t.GetNormalAt(Point(-0.5, 0.75, 0));
      auto n3 = t.GetNormalAt(Point(0.5, 0.25, 0));

      THEN("n1 == t.normal\
      \n\t And n2 == t.normal\
      \n\t And n3 == t.normal")
      {
        CHECK(n1 == t.normal);
        CHECK(n2 == t.normal);
        CHECK(n3 == t.normal);
      }
    }
  }
}

SCENARIO("Intersecting a ray parallel to the triangle")
{
  GIVEN("t = triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0))\
    \n\t And r = ray(point(0, -1, -2), vector(0, 1, 0))")
  {
    auto t = Triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
    auto r = Ray{ Point(0, -1, -2), Vector(0, 1, 0) };

    WHEN("xs = local_intersect(t, r)")
    {
      auto xs = t.Intersect(r);

      THEN("xs is empty") { CHECK(xs.Count() == 0); }
    }
  }
}

SCENARIO("A ray misses the p1-p3 edge")
{
  GIVEN("t = triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0))\
    \n\t And r = ray(point(1, 1, -2), vector(0, 0, 1))")
  {
    auto t = Triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
    auto r = Ray{ Point(1, 1, -2), Vector(0, 0, 1) };

    WHEN("xs = local_intersect(t, r)")
    {
      auto xs = t.Intersect(r);

      THEN("xs is empty") { CHECK(xs.Count() == 0); }
    }
  }
}

SCENARIO("A ray misses the p1-p2 edge")
{
  GIVEN("t = triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0))\
    \n\t And r = ray(point(-1, 1, -2), vector(0, 0, 1))")
  {
    auto t = Triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
    auto r = Ray{ Point(-1, 1, -2), Vector(0, 0, 1) };

    WHEN("xs = local_intersect(t, r)")
    {
      auto xs = t.Intersect(r);

      THEN("xs is empty") { CHECK(xs.Count() == 0); }
    }
  }
}

SCENARIO("A ray misses the p2-p3 edge")
{
  GIVEN("t = triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0))\
    \n\t And r = ray(point(0, -1, -2), vector(0, 0, 1))")
  {
    auto t = Triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
    auto r = Ray{ Point(0, -1, -2), Vector(0, 0, 1) };

    WHEN("xs = local_intersect(t, r)")
    {
      auto xs = t.Intersect(r);

      THEN("xs is empty") { CHECK(xs.Count() == 0); }
    }
  }
}

SCENARIO("A ray strikes a triangle")
{
  GIVEN("t = triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0))\
    \n\t And r = ray(point(0, 0.5, -2), vector(0, 0, 1))")
  {
    auto t = Triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
    auto r = Ray{ Point(0, 0.5, -2), Vector(0, 0, 1) };

    WHEN("xs = local_intersect(t, r)")
    {
      auto xs = t.Intersect(r);

      THEN("xs.count == 1\
      \n\t And xs[0].t == 2")
      {
        CHECK(xs.Count() == 1);
        CHECK(xs[0].t == 2);
      }
    }
  }
}
