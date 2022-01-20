// Test Framework
#include "doctest/doctest.h"

// Project Library
#include "Math/Matrix.hpp"
#include "Math/Tuple.hpp"
#include "Rendering/RayTracing/Ray.hpp"

SCENARIO("Creating and querying a ray")
{
  GIVEN("origin = point(1, 2, 3) && direction = vector(4, 5, 6)")
  {
    auto origin = make_point(1, 2, 3);
    auto direction = make_vector(4, 5, 6);

    WHEN("r = ray(origin, direction)")
    {
      auto r = Ray{ origin, direction };

      THEN("r.origin == origin && r.direction == direction")
      {
        CHECK(r.origin == origin);
        CHECK(r.direction == direction);
      }
    }
  }
}

SCENARIO("Computing a point from a distance")
{
  GIVEN("r = ray(point(2, 3, 4), vector(1, 0, 0))")
  {
    auto r = Ray{ make_point(2, 3, 4), make_vector(1, 0, 0) };

    THEN("position(r, 0) == point(2, 3, 4) &&\
    \n position(r, 1) == point(3, 3, 4) &&\
    \n position(r, -1) == point(1, 3, 4) &&\
    \n position(r, 2.5) == point(4.5, 3, 4)")
    {
      CHECK(position(r, 0) == make_point(2, 3, 4));
      CHECK(position(r, 1) == make_point(3, 3, 4));
      CHECK(position(r, -1) == make_point(1, 3, 4));
      CHECK(position(r, 2.5) == make_point(4.5, 3, 4));
    }
  }
}

SCENARIO("Translating a ray")
{
  GIVEN("r = ray(point(1, 2, 3), vector(0, 1, 0) && m = translation(3, 4, 5)")
  {
    auto r = Ray{ make_point(1, 2, 3), make_vector(0, 1, 0) };
    auto m = translation(3, 4, 5);

    WHEN("r2 = transform(r, m)")
    {
      auto r2 = transform(r, m);

      THEN("r2.origin == point(4, 6, 8) && r2.direction == vector(0, 1, 0)")
      {
        CHECK(r2.origin == make_point(4, 6, 8));
        CHECK(r2.direction == make_vector(0, 1, 0));
      }
    }
  }
}

SCENARIO("Scaling a ray")
{
  GIVEN("r = ray(point(1, 2, 3), vector(0, 1, 0) && m = scaling(2, 3, 4)")
  {
    auto r = Ray{ make_point(1, 2, 3), make_vector(0, 1, 0) };
    auto m = scaling(2, 3, 4);

    WHEN("r2 = transform(r, m)")
    {
      auto r2 = transform(r, m);

      THEN("r2.origin == point(2, 6, 12) && r2.direction == vector(0, 3, 0)")
      {
        CHECK(r2.origin == make_point(2, 6, 12));
        CHECK(r2.direction == make_vector(0, 3, 0));
      }
    }
  }
}
