// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

/// ===========================================================================
/// @section Stubs
/// ===========================================================================

class TestShape : public Shape
{
public:
  TestShape()
    : Shape()
    , saved_ray({ make_point(0, 0, 0), make_vector(0, 0, 1) })
  {}

  mutable Ray saved_ray;

protected:
  Tuple GetLocalNormalAt(Tuple point) const override
  {
    return make_vector(point.x, point.y, point.z);
  }

  Intersections VirtualIntersect(const Ray& r) const override
  {
    saved_ray = r;
    return {};
  }
};

/// ===========================================================================
/// @section Tests
/// ===========================================================================

SCENARIO("A shape's default transformation")
{
  GIVEN("s = shape()")
  {
    auto s = TestShape();

    THEN("s.transform == identity_matrix")
    {
      CHECK(s.GetTransform() == mat4::Identity());
    }
  }
}

SCENARIO("Changing a shape's transformation")
{
  GIVEN("s = shape() && t = translation(2, 3, 4)")
  {
    auto s = TestShape();
    auto t = translation(2, 3, 4);

    WHEN("set_transform(s, t)")
    {
      s.SetTransform(t);

      THEN("s.transform == t") { CHECK(s.GetTransform() == t); }
    }
  }
}

SCENARIO("A shape has a default material")
{
  GIVEN("s = shape()")
  {
    auto s = TestShape();

    WHEN("m = s.material")
    {
      auto m = s.GetMaterial();

      THEN("m == material()") { CHECK(m == Material()); }
    }
  }
}

SCENARIO("A shape may be assigned a material")
{
  GIVEN("s = shape() && m = material() && m.ambient = 1")
  {
    auto s = TestShape();
    auto m = Material();
    m.ambient = 1;

    WHEN("s.material = m")
    {
      s.SetMaterial(m);

      THEN("s.material == m") { CHECK(s.GetMaterial() == m); }
    }
  }
}

SCENARIO("Intersecting a scaled shape with a ray")
{
  GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1)) && s = shape()")
  {
    auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };
    auto s = TestShape();

    WHEN("set_transform(s, scaling(2, 2, 2)) && xs = intersect(s, r)")
    {
      s.SetTransform(scaling(2, 2, 2));
      auto xs = s.Intersect(r);

      THEN("s.saved_ray.origin == point(0, 0, -2.5) &&\
      \n s.saved_ray.direction == vector(0, 0, 0.5)")
      {
        CHECK(s.saved_ray.origin == make_point(0, 0, -2.5));
        CHECK(s.saved_ray.direction == make_vector(0, 0, 0.5));
      }
    }
  }
}

SCENARIO("Intersecting a translated shape with a ray")
{
  GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1)) && s = shape()")
  {
    auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };
    auto s = TestShape();

    WHEN("set_transform(s, scaling(2, 2, 2)) && xs = intersect(s, r)")
    {
      s.SetTransform(translation(5, 0, 0));
      auto xs = s.Intersect(r);

      THEN("s.saved_ray.origin == point(-5, 0,  -5) &&\
      \n s.saved_ray.direction == vector(0, 0, 1)")
      {
        CHECK(s.saved_ray.origin == make_point(-5, 0, -5));
        CHECK(s.saved_ray.direction == make_vector(0, 0, 1));
      }
    }
  }
}

SCENARIO("Computing the normal on a translated shape")
{
  GIVEN("s = shape() && set_transform(s, translation(0, 1, 0))")
  {
    auto s = TestShape();
    s.SetTransform(translation(0, 1, 0));

    WHEN("n = normal_at(s, point(0, 1.70711, -0.70711))")
    {
      auto n = s.GetNormalAt(make_point(0, 1.70711, -0.70711));

      THEN("n == vector(0, 0.70711, -0.70711)")
      {
        CHECK(n == make_vector(0, 0.70711, -0.70711));
      }
    }
  }
}

SCENARIO("Computing the normal on a transformed shape")
{
  GIVEN("s = shape() &&\
  \n m = scaling(1, 0.5, 1) * rotation_z(PI/5) &&\
  \n set_transform(s, translation(0, 1, 0))")
  {
    auto s = TestShape();
    auto matrix = scaling(1, 0.5, 1) * rotation_z(PI / 5);
    s.SetTransform(matrix);

    WHEN("n = normal_at(s, point(0, SQRT(2)/2, -SQRT(2)/2))")
    {
      auto sqrt2 = std::sqrt(2);
      auto sqrt2over2 = sqrt2 / 2;
      auto n = s.GetNormalAt(make_point(0, sqrt2over2, -sqrt2over2));

      THEN("n == vector(0, 0.97014, -0.24254)")
      {
        CHECK(n == make_vector(0, 0.97014, -0.24254));
      }
    }
  }
}
