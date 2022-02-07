// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

using namespace RayTracer::Math;

SCENARIO("A tuple with w = 1 is a point")
{
  GIVEN("a = Tuple(4.3, -4.2, 3.1, 1.0")
  {
    auto a = Tuple(4.3f, -4.2f, 3.1f, 1.0f);
    THEN("a.x == 4.3\
      && a.y == -4.2\
      && a.z == 3.1\
      && a.w == 1.0\
      && a is a point\
      && a is not a vector")
    {
      CHECK(a.x == 4.3f);
      CHECK(a.y == -4.2f);
      CHECK(a.z == 3.1f);
      CHECK(a.w == 1.0f);
      CHECK(isPoint(a));
      CHECK(!isVector(a));
    }
  }
}

SCENARIO("A tuple with w = 0 is a vector")
{
  GIVEN("a = Tuple(4.3, -4.2, 3.1, 1.0")
  {
    auto a = Tuple(4.3f, -4.2f, 3.1f, 0.0f);
    THEN("a.x == 4.3\
      && a.y == -4.2\
      && a.z == 3.1\
      && a.w == 0.0\
      && a is a vector\
      && a is not a point")
    {
      CHECK(a.x == 4.3f);
      CHECK(a.y == -4.2f);
      CHECK(a.z == 3.1f);
      CHECK(a.w == 0.0f);
      CHECK(!isPoint(a));
      CHECK(isVector(a));
    }
  }
}

SCENARIO("point() creates tuples with w=1")
{
  GIVEN("p = point(4, -4, 3)")
  {
    auto p = Point(4, -4, 3);
    THEN("p == tuple(4, -4, 3, 1)") { CHECK(p == Tuple(4, -4, 3, 1)); }
  }
}

SCENARIO("vector() creates tuples with w=0")
{
  GIVEN("p = point(4, -4, 3)")
  {
    auto p = Vector(4, -4, 3);
    THEN("p == tuple(4, -4, 3, 0)") { CHECK(p == Tuple(4, -4, 3, 0)); }
  }
}

SCENARIO("Adding two tuples")
{
  GIVEN("a1 = tuple(3, -2, 5, 1) && a2 = tuple(-2,3,1,0)")
  {
    auto a1 = Tuple(3, -2, 5, 1);
    auto a2 = Tuple(-2, 3, 1, 0);
    THEN("a1 + a2 == tuple(1, 1, 6, 1)")
    {
      CHECK(a1 + a2 == Tuple(1, 1, 6, 1));
    }
  }
}

SCENARIO("Subtracting two points")
{
  GIVEN("p1 = point(3, 2, 1) && p2 = point(5, 6, 7)")
  {
    auto p1 = Point(3, 2, 1);
    auto p2 = Point(5, 6, 7);
    THEN("p1 - p2 == vector(-2, -4, -6")
    {
      CHECK(p1 - p2 == Vector(-2, -4, -6));
    }
  }
}

SCENARIO("Subtracting a vector from a point")
{
  GIVEN("p = point(3, 2, 1) && v = vector(5, 6, 7)")
  {
    auto p = Point(3, 2, 1);
    auto v = Vector(5, 6, 7);
    THEN("p - v == point(-2, -4, -6") { CHECK(p - v == Point(-2, -4, -6)); }
  }
}

SCENARIO("Subtracting two vectors")
{
  GIVEN("v1 = vector(3, 2, 1) && v2 = vector(5, 6, 7)")
  {
    auto v1 = Vector(3, 2, 1);
    auto v2 = Vector(5, 6, 7);
    THEN("v1 - v2 == vector(-2, -4, -6")
    {
      CHECK(v1 - v2 == Vector(-2, -4, -6));
    }
  }
}

SCENARIO("Subtracting a vector from the zero vector")
{
  GIVEN("zero = vector(0, 0, 0) && v = vector(1, -2, 3)")
  {
    auto zero = Vector(0, 0, 0);
    auto v = Vector(1, -2, 3);
    THEN("zero - v == vector(-1, 2, -3)")
    {
      CHECK(zero - v == Vector(-1, 2, -3));
    }
  }
}

SCENARIO("Negating a tuple")
{
  GIVEN("a = tuple(1, -2, 3, -4)")
  {
    auto a = Tuple(1, -2, 3, -4);
    THEN("-a == tuple(-1, 2, -3, 4)") { CHECK(-a == Tuple(-1, 2, -3, 4)); }
  }
}

SCENARIO("Multiplying a tuple by a scalar")
{
  GIVEN("a = tuple(1, -2, 3, -4)")
  {
    auto a = Tuple(1, -2, 3, -4);
    THEN("a * 3.5 == tuple(3.5, -7, 10.5, -14)")
    {
      CHECK(a * 3.5 == Tuple(3.5, -7, 10.5, -14));
    }
  }
}

SCENARIO("Multiplying a tuple by a fraction")
{
  GIVEN("a = tuple(1, -2, 3, -4)")
  {
    auto a = Tuple(1, -2, 3, -4);
    THEN("a * 0.5 == tuple(0.5, -1, 1.5, -2)")
    {
      CHECK(a * 0.5 == Tuple(0.5, -1, 1.5, -2));
    }
  }
}

SCENARIO("Dividing a tuple by a scalar")
{
  GIVEN("a = tuple(1, -2, 3, -4)")
  {
    auto a = Tuple(1, -2, 3, -4);
    THEN("a / 2 == tuple(0.5, -1, 1.5, -2)")
    {
      CHECK(a / 2 == Tuple(0.5, -1, 1.5, -2));
    }
  }
}

SCENARIO("Computing the magnitude of vector(1, 0, 0)")
{
  GIVEN("v = vector(1, 0, 0)")
  {
    auto v = Vector(1, 0, 0);
    THEN("magnitude(v) == 1") { CHECK(magnitude(v) == 1); }
  }
}

SCENARIO("Computing the magnitude of vector(0, 1, 0)")
{
  GIVEN("v = vector(0, 1, 0)")
  {
    auto v = Vector(0, 1, 0);
    THEN("magnitude(v) == 1") { CHECK(magnitude(v) == 1); }
  }
}

SCENARIO("Computing the magnitude of vector(0, 0, 1)")
{
  GIVEN("v = vector(0, 0, 1)")
  {
    auto v = Vector(0, 0, 1);
    THEN("magnitude(v) == 1") { CHECK(magnitude(v) == 1); }
  }
}

SCENARIO("Computing the magnitude of vector(1, 2, 3)")
{
  GIVEN("v = vector(1, 2, 3)")
  {
    auto v = Vector(1, 2, 3);
    THEN("magnitude(v) == sqrt(14)")
    {
      CHECK(magnitude(v) == doctest::Approx(std::sqrt(14)));
    }
  }
}

SCENARIO("Computing the magnitude of vector(-1, -2, -3)")
{
  GIVEN("v = vector(-1, -2, -3)")
  {
    auto v = Vector(-1, -2, -3);
    THEN("magnitude(v) == sqrt(14)")
    {
      CHECK(magnitude(v) == doctest::Approx(std::sqrt(14)));
    }
  }
}

SCENARIO("Normalizing vector(4, 0, 0) gives (1, 0, 0)")
{
  GIVEN("v = vector(4, 0, 0)")
  {
    auto v = Vector(4, 0, 0);
    THEN("normalize(v) == vector(1, 0, 0)")
    {
      CHECK(normalize(v) == Vector(1, 0, 0));
    }
  }
}

SCENARIO("Normalizing vector(1, 2, 3)")
{
  GIVEN("v = vector(1, 2, 3)")
  {
    auto v = Vector(1, 2, 3);
    THEN("normalize(v) == approximately vector(")
    {
      auto sqrt14 = std::sqrt(14);
      CHECK(normalize(v) == Vector(1 / sqrt14, 2 / sqrt14, 3 / sqrt14));
    }
  }
}

SCENARIO("The magnitude of a  normalized vector")
{
  GIVEN("v = vector(1, 2, 3)")
  {
    auto v = Vector(1, 2, 3);
    WHEN("norm = normalize(v)")
    {
      auto norm = normalize(v);
      THEN("magnitude(norm) == 1")
      {
        CHECK(magnitude(norm) == doctest::Approx(1));
      }
    }
  }
}

SCENARIO("The dot product of two tuples")
{
  GIVEN("a = vector(1, 2, 3) && b = vector(2, 3, 4)")
  {
    auto a = Vector(1, 2, 3);
    auto b = Vector(2, 3, 4);
    THEN("dot(a, b) == 20") { CHECK(dot(a, b) == doctest::Approx(20)); }
  }
}

SCENARIO("The cross product of two tuples")
{
  GIVEN("a = vector(1, 2, 3) && b = vector(2, 3, 4)")
  {
    auto a = Vector(1, 2, 3);
    auto b = Vector(2, 3, 4);
    THEN("cross(a, b) == vector(-1, 2, -1)\
      && cross(b, a) == vector(1, -2, 1)")
    {
      CHECK(cross(a, b) == Vector(-1, 2, -1));
      CHECK(cross(b, a) == Vector(1, -2, 1));
    }
  }
}

SCENARIO("Reflecting a vector approaching at 45 degrees")
{
  GIVEN("v = vector(1, -1, 0) && n = vector(0, 1, 0)")
  {
    auto v = Vector(1, -1, 0);
    auto n = Vector(0, 1, 0);

    WHEN("r = reflect(v, n)")
    {
      auto r = reflect(v, n);

      THEN("r == vector(1, 1, 0)") { CHECK(r == Vector(1, 1, 0)); }
    }
  }
}

SCENARIO("Reflecting a vector off a slanted surface")
{
  GIVEN("v = vector(0, -1, 0) && n = vector(SQRT(2)/2, SQRT(2)/2, 0)")
  {
    auto v = Vector(0, -1, 0);
    auto n = Vector(std::sqrt(2) / 2, std::sqrt(2) / 2, 0);

    WHEN("r = reflect(v, n)")
    {
      auto r = reflect(v, n);

      THEN("r == vector(1, 0, 0)") { CHECK(r == Vector(1, 0, 0)); }
    }
  }
}
