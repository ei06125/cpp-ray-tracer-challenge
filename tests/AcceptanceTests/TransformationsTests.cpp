// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

using namespace RayTracer::Math;

SCENARIO("Multiplying by a translation matrix")
{
  GIVEN("transform = translation(5, -3, 2) && p = point(-3, 4, 5)")
  {
    auto transform = translation(5, -3, 2);
    auto p = Point(-3, 4, 5);
    THEN("transform * p == point(2, 1, 7)")
    {
      CHECK(transform * p == Point(2, 1, 7));
    }
  }
}

SCENARIO("Multiplying by the inverse of a translation matrix")
{
  GIVEN("transform = translation(5, -3, 2) &&\
  \n inv = inverse(transform) &&\
  \n p = point(-3, 4, 5)")
  {
    auto transform = translation(5, -3, 2);
    auto inv = inverse(transform);
    auto p = Point(-3, 4, 5);

    THEN("inv * p == point(-8, 7, 3)") { CHECK(inv * p == Point(-8, 7, 3)); }
  }
}

SCENARIO("Translation does not affect vectors")
{
  GIVEN("transform = translation(5, -3, 2) && v = vector(-3, 4, 5)")
  {
    auto transform = translation(5, -3, 2);
    auto v = Vector(-3, 4, 5);

    THEN("transform * v == v") { CHECK(transform * v == v); }
  }
}

SCENARIO("A scaling matrix applied to a point")
{
  GIVEN("transform = scaling(2, 3, 4) && p = point(-4, 6, 8)")
  {
    auto transform = scaling(2, 3, 4);
    auto p = Point(-4, 6, 8);

    THEN("transform * p == point(-8, 18, 32)")
    {
      CHECK(transform * p == Point(-8, 18, 32));
    }
  }
}

SCENARIO("A scaling matrix applied to a vector")
{
  GIVEN("transform = scaling(2, 3, 4) && v = vector(-4, 6, 8)")
  {
    auto transform = scaling(2, 3, 4);
    auto v = Vector(-4, 6, 8);

    THEN("transform * v == vector(-8, 18, 32)")
    {
      CHECK(transform * v == Vector(-8, 18, 32));
    }
  }
}

SCENARIO("Multiplying by the inverse of a scaling matrix")
{
  GIVEN("transform = scaling(2, 3, 4) &&\
  \n inv = inverse(transform) &&\
  \n v = vector(-4, 6, 8)")
  {
    auto transform = scaling(2, 3, 4);
    auto inv = inverse(transform);
    auto v = Vector(-4, 6, 8);

    THEN("inv * v == vector(-2, 2, 2)") { CHECK(inv * v == Vector(-2, 2, 2)); }
  }
}

SCENARIO("Reflection is scaling by a negative value")
{
  GIVEN("transform = scaling(-1, 1, 1) &&\
  \n p = point(2, 3, 4)")
  {
    auto transform = scaling(-1, 1, 1);
    auto p = Point(2, 3, 4);

    THEN("transform * p == point(-2, 3, 4)")
    {
      CHECK(transform * p == Point(-2, 3, 4));
    }
  }
}

SCENARIO("Rotating a point around the x axis")
{
  GIVEN("p = point(0, 1, 0) &&\
    \n half_quarter = rotation_x(PI / 4) &&\
    \n full_quarter = rotation_x(PI / 2)")
  {
    using namespace RayTracer::Math::Constants;
    auto p = Point(0, 1, 0);
    auto half_quarter = rotation_x(PI / 4);
    auto full_quarter = rotation_x(PI / 2);
    ;
    THEN("half_quarter * p == point(0, SQRT(2)/2, SQRT(2)/2) &&\
        \n full_quarter * p == point(0, 0, 1)")
    {
      CHECK(half_quarter * p == Point(0, std::sqrt(2) / 2, std::sqrt(2) / 2));
      CHECK(full_quarter * p == Point(0, 0, 1));
    }
  }
}

SCENARIO("The inverse of an x-rotation rotates in the opposite direction")
{
  GIVEN("p = point(0, 1, 0) &&\
    \n half_quarter = rotation_x(PI / 4) &&\
    \n inv = inverse(half_quarter)")
  {
    auto p = Point(0, 1, 0);
    auto half_quarter = rotation_x(PI / 4);
    auto inv = inverse(half_quarter);

    THEN("inv * p == point(0, SQRT(2)/2, -SQRT(2)/2)")
    {
      CHECK(inv * p == Point(0, std::sqrt(2) / 2, -(std::sqrt(2) / 2)));
    }
  }
}

SCENARIO("Rotating a point around the y axis")
{
  GIVEN("p = point(0, 0, 1) &&\
    \n half_quarter = rotation_y(PI / 4) &&\
    \n full_quarter = rotation_y(PI / 2)")
  {
    auto p = Point(0, 0, 1);
    auto half_quarter = rotation_y(PI / 4);
    auto full_quarter = rotation_y(PI / 2);
    ;
    THEN("half_quarter * p == point(SQRT(2)/2, 0, SQRT(2)/2) &&\
        \n full_quarter * p == point(1, 0, 0)")
    {
      CHECK(half_quarter * p == Point(std::sqrt(2) / 2, 0, std::sqrt(2) / 2));
      CHECK(full_quarter * p == Point(1, 0, 0));
    }
  }
}

SCENARIO("Rotating a point around the z axis")
{
  GIVEN("p = point(0, 1, 0) &&\
    \n half_quarter = rotation_z(PI / 4) &&\
    \n full_quarter = rotation_z(PI / 2)")
  {
    auto p = Point(0, 1, 0);
    auto half_quarter = rotation_z(PI / 4);
    auto full_quarter = rotation_z(PI / 2);
    ;
    THEN("half_quarter * p == point(-SQRT(2)/2, SQRT(2)/2, 0) &&\
        \n full_quarter * p == point(-1, 0, 0)")
    {
      CHECK(half_quarter * p ==
            Point(-(std::sqrt(2) / 2), std::sqrt(2) / 2, 0));
      CHECK(full_quarter * p == Point(-1, 0, 0));
    }
  }
}

SCENARIO("A shearing transformation moves x in proportion to y")
{
  GIVEN("transform = shearing(1, 0, 0, 0, 0, 0) && p = point(2, 3, 4)")
  {
    auto transform = shearing(1, 0, 0, 0, 0, 0);
    auto p = Point(2, 3, 4);

    THEN("transform * p == point(5, 3, 4)")
    {
      CHECK(transform * p == Point(5, 3, 4));
    }
  }
}

SCENARIO("A shearing transformation moves x in proportion to z")
{
  GIVEN("transform = shearing(0, 1, 0, 0, 0, 0) && p = point(2, 3, 4)")
  {
    auto transform = shearing(0, 1, 0, 0, 0, 0);
    auto p = Point(2, 3, 4);

    THEN("transform * p == point(6, 3, 4)")
    {
      CHECK(transform * p == Point(6, 3, 4));
    }
  }
}

SCENARIO("A shearing transformation moves y in proportion to x")
{
  GIVEN("transform = shearing(0, 0, 1, 0, 0, 0) && p = point(2, 3, 4)")
  {
    auto transform = shearing(0, 0, 1, 0, 0, 0);
    auto p = Point(2, 3, 4);

    THEN("transform * p == point(2, 5, 4)")
    {
      CHECK(transform * p == Point(2, 5, 4));
    }
  }
}

SCENARIO("A shearing transformation moves y in proportion to z")
{
  GIVEN("transform = shearing(0, 0, 0, 1, 0, 0) && p = point(2, 3, 4)")
  {
    auto transform = shearing(0, 0, 0, 1, 0, 0);
    auto p = Point(2, 3, 4);

    THEN("transform * p == point(2, 7, 4)")
    {
      CHECK(transform * p == Point(2, 7, 4));
    }
  }
}

SCENARIO("A shearing transformation moves z in proportion to x")
{
  GIVEN("transform = shearing(0, 0, 0, 0, 1, 0) && p = point(2, 3, 4)")
  {
    auto transform = shearing(0, 0, 0, 0, 1, 0);
    auto p = Point(2, 3, 4);

    THEN("transform * p == point(2, 3, 6)")
    {
      CHECK(transform * p == Point(2, 3, 6));
    }
  }
}

SCENARIO("A shearing transformation moves z in proportion to y")
{
  GIVEN("transform = shearing(0, 0, 0, 0, 0, 1) && p = point(2, 3, 4)")
  {
    auto transform = shearing(0, 0, 0, 0, 0, 1);
    auto p = Point(2, 3, 4);

    THEN("transform * p == point(2, 3, 7)")
    {
      CHECK(transform * p == Point(2, 3, 7));
    }
  }
}

SCENARIO("Individual transformations are applied in sequence")
{
  GIVEN("p = point(1, 0, 1) &&\
    \n A = rotation_x(PI / 2) &&\
    \n B = scaling(5, 5, 5) &&\
    \n C = translation(10, 5, 7)")
  {
    auto p = Point(1, 0, 1);
    auto A = rotation_x(PI / 2);
    auto B = scaling(5, 5, 5);
    auto C = translation(10, 5, 7);

    auto p2 = Point(0, 0, 0);
    auto p3 = Point(0, 0, 0);
    auto p4 = Point(0, 0, 0);

    // apply rotation first
    WHEN("p2 = A * p")
    {
      p2 = A * p;
      THEN("p2 == point(1, -1, 0)") { CHECK(p2 == Point(1, -1, 0)); }

      // then apply scaling
      AND_WHEN("p3 = B * p2")
      {
        p3 = B * p2;
        THEN("p3 == point(5, -5, 0)") { CHECK(p3 == Point(5, -5, 0)); }

        // then apply translation
        AND_WHEN("p4 = C * p3")
        {
          p4 = C * p3;
          THEN("p4 == point(15, 0, 7)") { CHECK(p4 == Point(15, 0, 7)); }
        }
      }
    }
  }
}

SCENARIO("Chained transformations must be applied in reverse order")
{
  GIVEN("auto p = point(1, 0, 1) &&\
    \n A = rotation_x(PI / 2) &&\
    \n B = scaling(5, 5, 5) &&\
    \n C = translation(10, 5, 7)")
  {
    auto p = Point(1, 0, 1);
    auto A = rotation_x(PI / 2);
    auto B = scaling(5, 5, 5);
    auto C = translation(10, 5, 7);

    WHEN("T = C * B * A")
    {
      auto T = C * B * A;

      THEN("T * p == point(15, 0, 7)") { CHECK(T * p == Point(15, 0, 7)); }
    }
  }
}

SCENARIO("The transformation matrix for the default orientation")
{
  GIVEN("from = point(0, 0, 0) && to = point(0, 0, -1) && up = vector(0, 1, 0)")
  {
    auto from = Point(0, 0, 0);
    auto to = Point(0, 0, -1);
    auto up = Vector(0, 1, 0);

    WHEN("t = view_transform(from, to, up)")
    {
      auto t = view_transform(from, to, up);

      THEN("t == scaling(-1, 1, -1)") { CHECK(t == mat4::Identity()); }
    }
  }
}

SCENARIO("A view transformation matrix looking in positive z direction")
{
  GIVEN("from = point(0, 0, 0) && to = point(0, 0, 1) && up = vector(0, 1, 0)")
  {
    auto from = Point(0, 0, 0);
    auto to = Point(0, 0, 1);
    auto up = Vector(0, 1, 0);

    WHEN("t = view_transform(from, to, up)")
    {
      auto t = view_transform(from, to, up);

      THEN("t == translation(0, 0, -8)") { CHECK(t == scaling(-1, 1, -1)); }
    }
  }
}

// The test positions the eye at a point 8 units along the z axis
SCENARIO("The view transformation moves the world")
{
  GIVEN("from = point(0, 0, 8) && to = point(0, 0, 0) && up = vector(0, 1, 0)")
  {
    auto from = Point(0, 0, 8);
    auto to = Point(0, 0, 0);
    auto up = Vector(0, 1, 0);

    WHEN("t = view_transform(from, to, up)")
    {
      auto t = view_transform(from, to, up);

      THEN("t == translation(0, 0, -8)") { CHECK(t == translation(0, 0, -8)); }
    }
  }
}

SCENARIO("An arbitrary view transformation")
{
  GIVEN("from = point(1, 2, 3) && to = point(4, -2, 8) && up = vector(1, 1, 0)")
  {
    auto from = Point(1, 3, 2);
    auto to = Point(4, -2, 8);
    auto up = Vector(1, 1, 0);

    WHEN("t = view_transform(from, to, up)")
    {
      auto t = view_transform(from, to, up);

      THEN("t is the following 4x4 matrix:\
      \n | -0.50709 | 0.50709 |  0.67612 | -2.36643 |\
      \n |  0.76772 | 0.60609 |  0.12122 | -2.82843 |\
      \n | -0.35857 | 0.59761 | -0.71714 |  0.00000 |\
      \n |  0.00000 | 0.00000 |  0.00000 |  1.00000 |")
      {
        mat4 expected = {
          -0.50709, 0.50709, 0.67612,  -2.36643, //
          0.76772,  0.60609, 0.12122,  -2.82843, //
          -0.35857, 0.59761, -0.71714, 0.00000,  //
          0.00000,  0.00000, 0.00000,  1.00000   //
        };

        CHECK(t == expected);
      }
    }
  }
}
