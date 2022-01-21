// Test Framework
#include "doctest/doctest.h"

// Project Library
#include "Math/Constants.hpp"
#include "Math/Tuple.hpp"
#include "Rendering/RayTracing/Intersection.hpp"
#include "Rendering/RayTracing/Material.hpp"
#include "Rendering/RayTracing/Ray.hpp"
#include "Rendering/RayTracing/Sphere.hpp"

SCENARIO("A ray intersects a sphere at two points")
{
  GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1)) &&\
  \n s = sphere()")
  {
    auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };
    auto s = Sphere();

    WHEN("xs = intersect(s, r)")
    {
      auto xs = intersect(s, r);

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
      auto xs = intersect(s, r);

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
      auto xs = intersect(s, r);

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
      auto xs = intersect(s, r);

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
      auto xs = intersect(s, r);

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
      auto xs = intersect(s, r);

      THEN("xs.count == 2 && xs[0].object == s && xs[1].object == s")
      {
        CHECK(xs.Count() == 2);
        CHECK(xs[0].object == s);
        CHECK(xs[1].object == s);
      }
    }
  }
}

SCENARIO("A sphere's default transformation")
{
  GIVEN("s = sphere()")
  {
    auto s = Sphere();

    THEN("s.transform == identity_matrix")
    {
      CHECK(s.transform == mat4::Identity());
    }
  }
}

SCENARIO("Changing a sphere's transformation")
{
  GIVEN("s = sphere() && t = translation(2, 3, 4)")
  {
    auto s = Sphere();
    auto t = translation(2, 3, 4);

    WHEN("set_transform(s, t)")
    {
      set_transform(s, t);

      THEN("s.transform == t") { CHECK(s.transform == t); }
    }
  }
}

SCENARIO("Intersecting a scaled sphere with a ray")
{
  GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1)) && s = sphere()")
  {
    auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };
    auto s = Sphere();

    WHEN("set_transform(s, scaling(2, 2, 2)) && xs = intersect(s, r)")
    {
      set_transform(s, scaling(2, 2, 2));
      auto xs = intersect(s, r);

      THEN("xs.count == 2 && xs[0].t == 3 && xs[1].t == 7")
      {
        CHECK(xs.Count() == 2);
        CHECK(xs[0].t == 3);
        CHECK(xs[1].t == 7);
      }
    }
  }
}

SCENARIO("Intersecting a translated sphere with a ray")
{
  GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1)) && s = sphere()")
  {
    auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };
    auto s = Sphere();

    WHEN("set_transform(s, scaling(2, 2, 2)) && xs = intersect(s, r)")
    {
      set_transform(s, translation(5, 0, 0));
      auto xs = intersect(s, r);

      THEN("xs.count == 0") { CHECK(xs.Count() == 0); }
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
      auto n = normal_at(s, make_point(1, 0, 0));

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
      auto n = normal_at(s, make_point(0, 1, 0));

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
      auto n = normal_at(s, make_point(0, 0, 1));

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
      auto n = normal_at(s, make_point(sqrt3over3, sqrt3over3, sqrt3over3));

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
      auto n = normal_at(s, make_point(sqrt3over3, sqrt3over3, sqrt3over3));

      THEN("n == normalize(n)") { CHECK(n == normalize(n)); }
    }
  }
}

SCENARIO("Computing the normal on a translated sphere")
{
  GIVEN("s = sphere() && set_transform(s, translation(0, 1, 0))")
  {
    auto s = Sphere();
    set_transform(s, translation(0, 1, 0));

    WHEN("n = normal_at(s, point(0, 1.70711, -0.70711))")
    {
      auto n = normal_at(s, make_point(0, 1.70711, -0.70711));

      THEN("n == vector(0, 0.70711, -0.70711)")
      {
        CHECK(n == make_vector(0, 0.70711, -0.70711));
      }
    }
  }
}

SCENARIO("Computing the normal on a transformed sphere")
{
  GIVEN("s = sphere() &&\
  \n m = scaling(1, 0.5, 1) * rotation_z(PI/5) &&\
  \n set_transform(s, translation(0, 1, 0))")
  {
    auto s = Sphere();
    auto m = scaling(1, 0.5, 1) * rotation_z(PI / 5);
    set_transform(s, m);

    WHEN("n = normal_at(s, point(0, SQRT(2)/2, -SQRT(2)/2))")
    {
      auto sqrt2 = std::sqrt(2);
      auto sqrt2over2 = sqrt2 / 2;
      auto n = normal_at(s, make_point(0, sqrt2over2, -sqrt2over2));

      THEN("n == vector(0, 0.97014, -0.24254)")
      {
        CHECK(n == make_vector(0, 0.97014, -0.24254));
      }
    }
  }
}

SCENARIO("A sphere has a default material")
{
  GIVEN("s = sphere()")
  {
    auto s = Sphere();

    WHEN("m = s.material")
    {
      auto m = s.material;

      THEN("m == material()") { CHECK(m == Material()); }
    }
  }
}

SCENARIO("A sphere may be assigned a material")
{
  GIVEN("s = sphere() && m = material() && m.ambient = 1")
  {
    auto s = Sphere();
    auto m = Material();
    m.ambient = 1;

    WHEN("s.material = m")
    {
      s.material = m;

      THEN("s.material == m") { CHECK(s.material == m); }
    }
  }
}
