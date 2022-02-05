// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

using namespace RayTracer::Math;
using namespace RayTracer::Rendering::Primitives;
using namespace RayTracer::Rendering::Parsers;

// ----------------------------------------------------------------------------
#define BACKGROUND()                                                           \
  GIVEN("p1 = point(0, 1, 0)\
\n\t And p2 = point(-1, 0, 0)\
\n\t And p3 = point(1, 0, 0)\
\n\t And n1 = vector(0, 1, 0)\
\n\t And n2 = vector(-1, 0, 0)\
\n\t And n3 = vector(1, 0, 0)")                                                \
  {                                                                            \
    auto p1 = make_point(0, 1, 0);                                             \
    auto p2 = make_point(-1, 0, 0);                                            \
    auto p3 = make_point(1, 0, 0);                                             \
    auto n1 = make_vector(0, 1, 0);                                            \
    auto n2 = make_vector(-1, 0, 0);                                           \
    auto n3 = make_vector(1, 0, 0);                                            \
                                                                               \
    WHEN("tri = smooth_triangle(p1, p2, p3, n1, n2, n3)")                      \
    {                                                                          \
      auto tri = SmoothTriangle(p1, p2, p3, n1, n2, n3);
// ----------------------------------------------------------------------------

SCENARIO("Constructing a smooth triangle")
{
  BACKGROUND()

  THEN("tri.p1 == p1\
    \n\t And tri.p2 == p2\
    \n\t And tri.p3 == p3\
    \n\t And tri.n1 == n1\
    \n\t And tri.n2 == n2\
    \n\t And tri.n3 == n3")
  {
    CHECK(tri.p1 == p1);
    CHECK(tri.p1 == p1);
    CHECK(tri.p1 == p1);
    CHECK(tri.p1 == p1);
    CHECK(tri.p1 == p1);
    CHECK(tri.p1 == p1);
    CHECK(tri.p1 == p1);
  }
} // WHEN
} // GIVEN
} // SCENARIO

SCENARIO("An intersection with a smooth triangle stores u and v")
{
  BACKGROUND()

  AND_WHEN("r = ray(point(-0.2, 0.3, -2), vector(0, 0, 1))\
    \n\t And xs = local_intersection(tri, r)")
  {
    auto r = Ray{ make_point(-0.2, 0.3, -2), make_vector(0, 0, 1) };
    auto xs = tri.Intersect(r);

    THEN("xs[0].u == 0.45 And xs[0].v == 0.25")
    {
      CHECK(xs[0].u == 0.45f);
      CHECK(xs[0].v == 0.25f);
    }
  }
} // WHEN
} // GIVEN
} // SCENARIO

SCENARIO("A smooth triangle uses u and v to interpolate the normal")
{
  BACKGROUND()

  AND_WHEN("i = intersection_with_uv(1, tri, 0.45, 0.25)\
  \n\t And n = normal_at(tri, point(0, 0, 0), i)")
  {
    auto i = Intersection{ 3.5, &tri, 0.45, 0.25 };
    auto n = tri.GetNormalAt(make_point(0, 0, 0), &i);

    THEN("n == vector(-0.5547, 0.83205, 0)")
    {
      CHECK(n == make_vector(-0.5547, 0.83205, 0));
    }
  }
} // WHEN
} // GIVEN
} // SCENARIO

SCENARIO("Preparing the normal on a smooth triangle")
{

  BACKGROUND()

  AND_WHEN("i = intersection_with_uv(1, tri, 0.45, 0.25)\
  \n\t And r = ray(point(-0.2, 0.3, -2), vector(0, 0, 1))\
  \n\t xs = intersections(i)\
  \n\t And comps = prepare_computations(i, r, xs)")
  {
    auto i = Intersection{ 3.5, &tri, 0.45, 0.25 };
    auto r = Ray{ make_point(-0.2, 0.3, -2), make_vector(0, 0, 1) };
    auto xs = Intersections({ i });
    auto comps = prepare_computations(i, r, &xs);

    THEN("comps.normalv == vector(-0.5547, 0.83205, 0)")
    {
      CHECK(comps.normalv == make_vector(-0.5547, 0.83205, 0));
    }
  }
} // WHEN
} // GIVEN
} // SCENARIO

//
/// ---
#undef BACKGROUND
