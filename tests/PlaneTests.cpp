// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

SCENARIO("The normal of a plane is constant everywhere")
{
  GIVEN("p = plane()")
  {
    auto p = Plane();

    WHEN("n1 = local_normal_at(p, point(0, 0, 0)) &&\
        \n n2 = local_normal_at(p, point(10, 0, -10)) &&\
        \n n3 = local_normal_at(p, point(-5, 0, 150))")
    {
      auto n1 = p.GetNormalAt(make_point(0, 0, 0));
      auto n2 = p.GetNormalAt(make_point(10, 0, -10));
      auto n3 = p.GetNormalAt(make_point(-5, 0, 150));

      THEN("n1 == vector(0, 1, 0) &&\
            \n n2 == vector(0, 1, 0) &&\
            \n n3 == vector(0, 1, 0)")
      {
        CHECK(n1 == make_vector(0, 1, 0));
        CHECK(n2 == make_vector(0, 1, 0));
        CHECK(n3 == make_vector(0, 1, 0));
      }
    }
  }
}

SCENARIO("Intersect with a ray parallel to the plane")
{
  GIVEN("p = plane() && r = ray(point(0, 10, 0), vector(0, 0, 1))")
  {
    auto p = Plane();
    auto r = Ray({ make_point(0, 10, 0), make_vector(0, 0, 1) });

    WHEN("xs = local_intersect(p, r)")
    {
      auto xs = p.Intersect(r);

      THEN("xs is empty") { CHECK(xs.Count() == 0); }
    }
  }
}

SCENARIO("Intersect with a coplanar ray")
{
  GIVEN("p = plane() && r = ray(point(0, 0, 0), vector(0, 0, 1))")
  {
    auto p = Plane();
    auto r = Ray({ make_point(0, 0, 0), make_vector(0, 0, 1) });

    WHEN("xs = local_intersect(p, r)")
    {
      auto xs = p.Intersect(r);

      THEN("xs is empty") { CHECK(xs.Count() == 0); }
    }
  }
}

SCENARIO("A ray intersecting a plane from above")
{
  GIVEN("p = plane() && r = ray(point(0, 1, 0), vector(0, -1, 0))")
  {
    auto p = Plane();
    auto r = Ray({ make_point(0, 1, 0), make_vector(0, -1, 0) });

    WHEN("xs = local_intersect_at(p, r)")
    {
      auto xs = p.Intersect(r);

      THEN("xs.count == 1 && xs[0].t == 1 && xs[0].object == p")
      {
        CHECK(xs.Count() == 1);
        CHECK(xs[0].t == 1);
        CHECK(xs[0].object == p);
      }
    }
  }
}

SCENARIO("A ray intersecting a plane from below")
{
  GIVEN("p = plane() && r = ray(point(0, -1, 0), vector(0, 1, 0))")
  {
    auto p = Plane();
    auto r = Ray({ make_point(0, -1, 0), make_vector(0, 1, 0) });

    WHEN("xs = local_intersect_at(p, r)")
    {
      auto xs = p.Intersect(r);

      THEN("xs.count == 1 && xs[0].t == 1 && xs[0].object == p")
      {
        CHECK(xs.Count() == 1);
        CHECK(xs[0].t == 1);
        CHECK(xs[0].object == p);
      }
    }
  }
}
