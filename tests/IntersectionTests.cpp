// Test Framework
#include "doctest/doctest.h"

// Project Library
#include "Rendering/RayTracing/Intersection.hpp"
#include "Rendering/RayTracing/Sphere.hpp"

SCENARIO("An intersection encapsulates t and object")
{
  GIVEN("s = sphere()")
  {
    auto s = Sphere();

    WHEN("i = intersection(3.5, s)")
    {
      auto i = Intersection(3.5, s);

      THEN("i.t == 3.5 && i.object == s")
      {
        CHECK(i.t == 3.5);
        CHECK(i.object == s);
      }
    }
  }
}

SCENARIO("Aggregating intersections")
{
  GIVEN("s = sphere() &&\
    \n i1 = intersection(1, s) &&\
    \n i2 = intersection(2, s)")
  {
    auto s = Sphere();
    auto i1 = Intersection(1, s);
    auto i2 = Intersection(2, s);

    WHEN("xs = intersections(i1, i2)")
    {
      auto xs = Intersections({ i1, i2 });

      THEN("xs.count == 2 && xs[0].t == 1 && xs[1].t == 2")
      {
        CHECK(xs.Count() == 2);
        CHECK(xs[0].t == 1);
        CHECK(xs[1].t == 2);
      }
    }
  }
}

SCENARIO("The hit, when all intersections have positive t")
{
  GIVEN("s = sphere() &&\
    \n i1 = intersection(1, s) &&\
    \n i2 = intersection(2, s) &&\
    \n xs = intersections(i2, i1)")
  {
    auto s = Sphere();
    auto i1 = Intersection(1, s);
    auto i2 = Intersection(2, s);
    auto xs = Intersections({ i2, i1 });

    WHEN("i = hit(xs)")
    {
      auto i = hit(xs);

      THEN("i == i1")
      {
        REQUIRE(i != nullptr);
        CHECK(*i == i1);
      }
    }
  }
}

SCENARIO("The hit, when some intersections have negative t")
{
  GIVEN("s = sphere() &&\
    \n i1 = intersection(-1, s) &&\
    \n i2 = intersection(1, s) &&\
    \n xs = intersections(i2, i1)")
  {

    auto s = Sphere();
    auto i1 = Intersection(-1, s);
    auto i2 = Intersection(1, s);
    auto xs = Intersections({ i2, i1 });

    WHEN("i = hit(xs)")
    {
      auto i = hit(xs);

      THEN("i == i2")
      {
        REQUIRE(i != nullptr);
        CHECK(*i == i2);
      }
    }
  }
}

SCENARIO("The hit, when all intersections have negative t")
{
  GIVEN("s = sphere() &&\
    \n i1 = intersection(-2, s) &&\
    \n i2 = intersection(-1, s) &&\
    \n xs = intersections(i2, i1)")
  {

    auto s = Sphere();
    auto i1 = Intersection(-2, s);
    auto i2 = Intersection(-1, s);
    auto xs = Intersections({ i2, i1 });

    WHEN("i = hit(xs)")
    {
      auto i = hit(xs);

      THEN("i is nothing") { CHECK(i == nullptr); }
    }
  }
}

SCENARIO("The hit is always the lowest nonnegative intersection")
{
  GIVEN("s = sphere() &&\
    \n i1 = intersection(5, s) &&\
    \n i2 = intersection(7, s) &&\
    \n i3 = intersection(-3, s) &&\
    \n i4 = intersection(2, s) &&\
    \n xs = intersections(i1, i2, i3, i4)")
  {

    auto s = Sphere();
    auto i1 = Intersection(5, s);
    auto i2 = Intersection(7, s);
    auto i3 = Intersection(-3, s);
    auto i4 = Intersection(2, s);
    auto xs = Intersections({ i1, i2, i3, i4 });

    WHEN("i = hit(xs)")
    {
      auto i = hit(xs);

      THEN("i == i4")
      {
        REQUIRE(i != nullptr);
        CHECK(*i == i4);
      }
    }
  }
}
