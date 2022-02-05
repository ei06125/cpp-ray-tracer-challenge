// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

#include <array>

using namespace RayTracer::Rendering::Primitives;
using namespace RayTracer::Rendering::Lighting;

SCENARIO("An intersection encapsulates t and object")
{
  GIVEN("s = sphere()")
  {
    auto s = Sphere();

    WHEN("i = intersection(3.5, s)")
    {
      auto i = Intersection(3.5, &s);

      THEN("i.t == 3.5 && i.object == s")
      {
        CHECK(i.t == 3.5);
        CHECK(*i.object == s);
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
    auto i1 = Intersection(1, &s);
    auto i2 = Intersection(2, &s);

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
    auto i1 = Intersection(1, &s);
    auto i2 = Intersection(2, &s);
    auto xs = Intersections({ i2, i1 });

    WHEN("i = hit(xs)")
    {
      auto i = xs.Hit();

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
    auto i1 = Intersection(-1, &s);
    auto i2 = Intersection(1, &s);
    auto xs = Intersections({ i2, i1 });

    WHEN("i = hit(xs)")
    {
      auto i = xs.Hit();

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
    auto i1 = Intersection(-2, &s);
    auto i2 = Intersection(-1, &s);
    auto xs = Intersections({ i2, i1 });

    WHEN("i = hit(xs)")
    {
      auto i = xs.Hit();

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
    auto i1 = Intersection(5, &s);
    auto i2 = Intersection(7, &s);
    auto i3 = Intersection(-3, &s);
    auto i4 = Intersection(2, &s);
    auto xs = Intersections({ i1, i2, i3, i4 });

    WHEN("i = hit(xs)")
    {
      auto i = xs.Hit();

      THEN("i == i4")
      {
        REQUIRE(i != nullptr);
        CHECK(*i == i4);
      }
    }
  }
}

SCENARIO("Precomputing the state of an intersection")
{
  GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1)) &&\
  \n shape = sphere() && i = Intersection(4, shape)")
  {
    auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };
    auto shape = Sphere();
    auto i = Intersection(4, &shape);

    WHEN("comps = prepare_computations(i, r)")
    {
      auto comps = prepare_computations(i, r);

      THEN("comps.t == i.t &&\
      \n comps.object == i.object &&\
      \n comps.point == point(0, 0, -1) &&\
      \n comps.eyev == vector(0, 0, -1) &&\
      \n comps.normalv == vector(0, 0, -1)")
      {
        CHECK(comps.t == i.t);
        CHECK(comps.object == i.object);
        CHECK(comps.point == make_point(0, 0, -1));
        CHECK(comps.eyev == make_vector(0, 0, -1));
        CHECK(comps.normalv == make_vector(0, 0, -1));
      }
    }
  }
}

SCENARIO("The hit, when an intersection occurs on the outside")
{
  GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1)) &&\
  \n shape = sphere() && i = Intersection(4, shape)")
  {
    auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };
    auto shape = Sphere();
    auto i = Intersection(4, &shape);

    WHEN("comps = prepare_computations(i, r)")
    {
      auto comps = prepare_computations(i, r);

      THEN("comps.inside == false") { CHECK(comps.inside == false); }
    }
  }
}

SCENARIO("The hit, when an intersection occurs on the inside")
{
  GIVEN("r = ray(point(0, 0, 0), vector(0, 0, 1)) &&\
  \n shape = sphere() && i = Intersection(1, shape)")
  {
    auto r = Ray{ make_point(0, 0, 0), make_vector(0, 0, 1) };
    auto shape = Sphere();
    auto i = Intersection(1, &shape);

    WHEN("comps = prepare_computations(i, r)")
    {
      auto comps = prepare_computations(i, r);

      THEN("comps.point == point(0, 0, 1) &&\
      \n comps.eyev == vector(0, 0, -1) &&\
      \n comps.inside == true &&\
      \n comps.normalv == vector(0, 0, -1)")
      {
        CHECK(comps.point == make_point(0, 0, 1));
        CHECK(comps.eyev == make_vector(0, 0, -1));
        CHECK(comps.inside == true);
        // normal would have been (0, 0, 1), but is inverted!
        CHECK(comps.normalv == make_vector(0, 0, -1));
      }
    }
  }
}

/// ===========================================================================
/// @section Shadows
/// ===========================================================================

SCENARIO("The hit should offset the point")
{
  GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1)) &&\
  \n shape = sphere() with:\
  \n | transform | translation(0, 0, 1) | &&\
  \n i = intersection(5, shape)")
  {

    auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };
    auto shape = Sphere();
    shape.SetTransform(translation(0, 0, 1));
    auto i = Intersection(5, &shape);

    WHEN("comps = prepare_computations(i, r)")
    {
      auto comps = prepare_computations(i, r);

      THEN("comps.over_point.z < -EPSILON/2 &&\
      \n comps.point.z > comps.over_point.z")
      {
        CHECK(comps.over_point.z < EPSILON / -2.0f);
        CHECK(comps.point.z > comps.over_point.z);
      }
    }
  }
}

/// ===========================================================================
/// @section Reflection
/// ===========================================================================

SCENARIO("Precomputing the reflection vector")
{
  GIVEN("shape = plane() &&\
  \n r = ray(point(0, 1, -1), vector(0, -SQRT(2)/2, SQRT(2)/2)) &&\
  \n i = intersection(SQRT(2), shape)")
  {
    auto shape = Plane();
    auto sqrt2 = std::sqrt(2);
    auto r = Ray{ make_point(0, 1, -1), make_vector(0, -sqrt2 / 2, sqrt2 / 2) };
    auto i = Intersection(sqrt2, &shape);

    WHEN("comps = prepare_computations(i, r)")
    {
      auto comps = prepare_computations(i, r);

      THEN("comps.reflectv == vector(0, SQRT(2)/2, SQRT(2)/2)")
      {
        CHECK(comps.reflectv == make_vector(0, sqrt2 / 2, sqrt2 / 2));
      }
    }
  }
}

/// ===========================================================================
/// @section Refraction
/// ===========================================================================

SCENARIO("Finding n1 and n2 at various intersections")
{
  GIVEN("A = glass_sphere() with:\
  \n | transform                 | scaling(2, 2, 2) |\
  \n | material.refractive_index | 1.5              |\
  \n AND B = glass_sphere() with:\
  \n | transform                 | translation(0, 0, -0.25) |\
  \n | material.refractive_index | 2.0                      |\
  \n AND C = glass_sphere() with:\
  \n | transform                 | translation(0, 0, 0.25) |\
  \n | material.refractive_index | 2.5                     |\
  \n AND r = ray(point(0, 0, -4), vector(0, 0, 1))\
  \n AND xs = intersections(2:A, 2.75:B, 3.25:C, 4.75:B, 5.25:C, 6:A)")
  {
    auto A = GlassSphere();
    A.SetTransform(scaling(2, 2, 2));
    A.SetMaterial().refractiveIndex = 1.5;

    auto B = GlassSphere();
    B.SetTransform(translation(0, 0, -0.25));
    B.SetMaterial().refractiveIndex = 2.0;

    auto C = GlassSphere();
    C.SetTransform(translation(0, 0, 0.25));
    C.SetMaterial().refractiveIndex = 2.5;

    const auto r = Ray{ make_point(0, 0, -4), make_vector(0, 0, 1) };
    const Intersections xs{ { 2, &A },    { 2.75, &B }, { 3.25, &C },
                            { 4.75, &B }, { 5.25, &C }, { 6, &A } };

    /// -----------------------------------------------------------------------
    /// @subsection Example Test Data

    struct TestData
    {
      std::size_t index;
      float n1;
      float n2;
    };

    const std::array<TestData, 6> testData{ {
      { 0, 1.0, 1.5 }, // 0 -> A
      { 1, 1.5, 2.0 }, // A -> B
      { 2, 2.0, 2.5 }, // B -> C
      { 3, 2.5, 2.5 }, // C -> C
      { 4, 2.5, 1.5 }, // C -> A
      { 5, 1.5, 1.0 }  // A -> 0
    } };
    /// -----------------------------------------------------------------------

    std::vector<const Shape*> objects{};
    for (const auto& [index, n1, n2] : testData) {
      auto comps = prepare_computations(xs[index], r, &xs, &objects);
      {
        CHECK(comps.n1 == n1);
        CHECK(comps.n2 == n2);
      }
    }
  }
}

SCENARIO("The under point is offset below the surface")
{
  GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1)) &&\
  \n shape = glass_sphere() with:\
  \n | transform | translation(0, 0, 1) |\
  \n AND i = intersection(5, shape) &&\
  \n xs = intersections(i)")
  {
    auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };
    auto shape = GlassSphere();
    shape.SetTransform(translation(0, 0, 1));
    auto i = Intersection(5, &shape);
    const Intersections xs({ i });

    WHEN("comps = prepare_computations(i, r, xs")
    {
      auto comps = prepare_computations(i, r, &xs);

      THEN("comps.under_point.z > EPSILON/2 &&\
      \n comps.point.z < comps.under_point.z")
      {
        CHECK(comps.under_point.z > EPSILON / 2);
        CHECK(comps.point.z < comps.under_point.z);
      }
    }
  }
}

/// ===========================================================================
/// @section Fresnel Effect (Schlick Approximation)
/// ===========================================================================

// SCENARIO("The Schlick approximation under total internal reflection")
// {
//   GIVEN("shape = glass_sphere()\
//   \n\t And r = ray(point(0, 0, SQRT(2)/2), vector(0, 1, 0))\
//   \n\t And xs = intersections(-SQRT(2)/2:shape, SQRT(2)/2:shape)")
//   {
//     auto shape = GlassSphere();
//     float sqrt2 = std::sqrt(2);
//     auto r = Ray{ make_point(0, 0, sqrt2 / 2), make_vector(0, 1, 0) };
//     auto xs = Intersections{ { -sqrt2 / 2, &shape }, { sqrt2 / 2, &shape } };

//     WHEN("comps = prepare_computations(xs[1], r, xs)\
//     \n\t And reflectance = schlick(comps)")
//     {
//       auto comps = prepare_computations(xs[1], r, &xs);
//       auto reflectance = schlick(comps);

//       THEN("reflectance == 1.0") { CHECK(reflectance == 1.0); }
//     }
//   }
// }

// SCENARIO("The Schlick approximation with a perpendicular viewing angle")
// {
//   GIVEN("shape = glass_sphere()\
//   \n\t And r = ray(point(0, 0, 0), vector(0, 1, 0))\
//   \n\t And xs = intersections(-1:shape, 1:shape)")
//   {
//     auto shape = GlassSphere();
//     auto r = Ray{ make_point(0, 0, 0), make_vector(0, 1, 0) };
//     auto xs = Intersections{ { -1, &shape }, { 1, &shape } };

//     WHEN("comps = prepare_computations(xs[1], r, xs)\
//     \n\t And reflectance = schlick(comps)")
//     {
//       auto comps = prepare_computations(xs[1], r, &xs);
//       auto reflectance = schlick(comps);

//       THEN("reflectance == 0.4") { CHECK(reflectance == 0.4); }
//     }
//   }
// }

// SCENARIO("The Schlick approximation with small angle and n2 > n1")
// {
//   GIVEN("shape = glass_sphere()\
//   \n\t And r = ray(point(0, 0.99, -2), vector(0, 0, 1))\
//   \n\t And xs = intersections(1.8589:shape)")
//   {
//     auto shape = GlassSphere();
//     auto r = Ray{ make_point(0, 0.99, -2), make_vector(0, 0, 1) };
//     auto xs = Intersections{ { 1.8589, &shape } };

//     WHEN("comps = prepare_computations(xs[0], r, xs)\
//     \n\t And reflectance = schlick(comps)")
//     {
//       auto comps = prepare_computations(xs[0], r, &xs);
//       auto reflectance = schlick(comps);

//       THEN("reflectance == 0.48873")
//       {
//         CHECK(reflectance == doctest::Approx(0.48873));
//       }
//     }
//   }
// }

SCENARIO("An intersection can encapsulate 'u' and 'v'")
{
  GIVEN("s = triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0))")
  {
    auto s =
      Triangle(make_point(0, 1, 0), make_point(-1, 0, 0), make_point(1, 0, 0));

    WHEN("i = intersection_with_uv(3.5, s, 0.2, 0.4)")
    {
      auto i = Intersection{ 3.5, &s, 0.2, 0.4 };
      THEN("i.u == 0.2 And i.v == 0.4")
      {
        CHECK(i.u == 0.2f);
        CHECK(i.v == 0.4f);
      }
    }
  }
}
