// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

using namespace RayTracer::Rendering::Primitives;
using namespace RayTracer::Rendering::Lighting;
using namespace RayTracer::Math;

SCENARIO("A ray intersects a sphere at two points")
{
  GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1)) &&\
  \n s = sphere()")
  {
    auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };
    auto s = Sphere();

    WHEN("xs = intersect(s, r)")
    {
      auto xs = s.Intersect(r);

      THEN("xs.count == 2 && xs[0] == 4.0 && xs[1] == 6.0")
      {
        CHECK(xs.Count() == 2);
        CHECK(xs[0].t == 4.0);
        CHECK(xs[1].t == 6.0);
      }
    }
  }
}

SCENARIO("A ray intersects a sphere at a tangent")
{
  GIVEN("r = ray(point(0, 1, -5), vector(0, 0, 1)) &&\
    \n s = sphere()")
  {
    auto r = Ray{ make_point(0, 1, -5), make_vector(0, 0, 1) };
    auto s = Sphere();

    WHEN("xs = intersect(s, r)")
    {
      auto xs = s.Intersect(r);

      THEN("xs.count == 2 && xs[0] == 5.0 && xs[1] == 5.0")
      {
        CHECK(xs.Count() == 2);
        CHECK(xs[0].t == 5.0);
        CHECK(xs[1].t == 5.0);
      }
    }
  }
}

SCENARIO("A ray misses a sphere")
{
  GIVEN("r = ray(point(0, 2, -5), vector(0, 0, 1)) &&\
    \n s = sphere()")
  {
    auto r = Ray{ make_point(0, 2, -5), make_vector(0, 0, 1) };
    auto s = Sphere();

    WHEN("xs = intersect(s, r)")
    {
      auto xs = s.Intersect(r);

      THEN("xs.count == 0") { CHECK(xs.Count() == 0); }
    }
  }
}

SCENARIO("A ray originates inside a sphere")
{
  GIVEN("r = ray(point(0, 0, 0), vector(0, 0, 1)) &&\
    \n s = sphere()")
  {
    auto r = Ray{ make_point(0, 0, 0), make_vector(0, 0, 1) };
    auto s = Sphere();

    WHEN("xs = intersect(s, r)")
    {
      auto xs = s.Intersect(r);

      THEN("xs.count == 2 && xs[0] == -1.0 && xs[1] == 1.0")
      {
        CHECK(xs.Count() == 2);
        CHECK(xs[0].t == -1.0);
        CHECK(xs[1].t == 1.0);
      }
    }
  }
}

SCENARIO("A sphere is behind a ray")
{
  GIVEN("r = ray(point(0, 0, 5), vector(0, 0, 1)) &&\
    \n s = sphere()")
  {
    auto r = Ray{ make_point(0, 0, 5), make_vector(0, 0, 1) };
    auto s = Sphere();

    WHEN("xs = intersect(s, r)")
    {
      auto xs = s.Intersect(r);

      THEN("xs.count == 2 && xs[0] == -6.0 && xs[1] == -4.0")
      {
        CHECK(xs.Count() == 2);
        CHECK(xs[0].t == -6.0);
        CHECK(xs[1].t == -4.0);
      }
    }
  }
}

SCENARIO("Intersect sets the object on the intersection")
{
  GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1) && s = sphere()")
  {
    auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };
    auto s = Sphere();

    WHEN("xs = intersect(s, r)")
    {
      auto xs = s.Intersect(r);

      THEN("xs.count == 2 && xs[0].object == s && xs[1].object == s")
      {
        CHECK(xs.Count() == 2);
        CHECK(*xs[0].object == s);
        CHECK(*xs[1].object == s);
      }
    }
  }
}

SCENARIO("The normal on a sphere at a point on the x axis")
{
  GIVEN("s = sphere()")
  {
    auto s = Sphere();

    WHEN("n = normal_at(s, point(1, 0, 0))")
    {
      auto n = s.GetNormalAt(make_point(1, 0, 0));

      THEN("n == vector(1, 0, 0)") { CHECK(n == make_vector(1, 0, 0)); }
    }
  }
}

SCENARIO("The normal on a sphere at a point on the y axis")
{
  GIVEN("s = sphere()")
  {
    auto s = Sphere();

    WHEN("n = normal_at(s, point(0, 1, 0))")
    {
      auto n = s.GetNormalAt(make_point(0, 1, 0));

      THEN("n == vector(0, 1, 0)") { CHECK(n == make_vector(0, 1, 0)); }
    }
  }
}

SCENARIO("The normal on a sphere at a point on the z axis")
{
  GIVEN("s = sphere()")
  {
    auto s = Sphere();

    WHEN("n = normal_at(s, point(0, 0, 1))")
    {
      auto n = s.GetNormalAt(make_point(0, 0, 1));

      THEN("n == vector(0, 0, 1)") { CHECK(n == make_vector(0, 0, 1)); }
    }
  }
}

SCENARIO("The normal on a sphere at a nonaxial point")
{
  GIVEN("s = sphere()")
  {
    auto s = Sphere();

    WHEN("n = normal_at(s, point(SQRT(3)/3, SQRT(3)/3, SQRT(3)/3))")
    {
      auto sqrt3 = std::sqrt(3);
      auto sqrt3over3 = sqrt3 / 3;
      auto n = s.GetNormalAt(make_point(sqrt3over3, sqrt3over3, sqrt3over3));

      THEN("n == vector(SQRT(3)/3, SQRT(3)/3, SQRT(3)/3))")
      {
        CHECK(n == make_vector(sqrt3over3, sqrt3over3, sqrt3over3));
      }
    }
  }
}

SCENARIO("The normal is a normalized vector")
{
  GIVEN("s = sphere()")
  {
    auto s = Sphere();

    WHEN("n = normal_at(s, point(SQRT(3)/3, SQRT(3)/3, SQRT(3)/3))")
    {
      auto sqrt3 = std::sqrt(3);
      auto sqrt3over3 = sqrt3 / 3;
      auto n = s.GetNormalAt(make_point(sqrt3over3, sqrt3over3, sqrt3over3));

      THEN("n == normalize(n)") { CHECK(n == normalize(n)); }
    }
  }
}

/// ===========================================================================
/// @section Refraction
/// ===========================================================================

SCENARIO("A helper for producing a sphere with a glassy material")
{
  GIVEN("s = glass_sphere()")
  {
    auto s = GlassSphere();

    THEN("s.transform == identity_matrix &&\
    \n s.material.transparency == 1.0 &&\
    \n s.material.refractive_index == 1.5")
    {
      CHECK(s.GetTransform() == mat4::Identity());
      CHECK(s.GetMaterial().transparency == 1.0);
      CHECK(s.GetMaterial().refractiveIndex == 1.5);
    }
  }
}
