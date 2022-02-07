// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

using namespace RayTracer::Rendering::Primitives;
using namespace RayTracer::Math;

SCENARIO("CSG is created with an operation and two shapes")
{
  GIVEN("s1 = sphere()\
    \n\t And s2 = cube()")
  {
    auto s1 = CreateShape<Sphere>();
    auto s2 = CreateShape<Cube>();

    WHEN("c = csg('union', s1, s2)")
    {
      auto c = CreateCSGShape(CSGOperation::Union, s1, s2);

      THEN("c.operation == 'union'\
            \n\t And c.left == s1\
            \n\t And c.right == s2\
            \n\t s1.parent == c\
            \n\t And s2.parent == c")
      {
        CHECK(c->GetOperation() == CSGOperation::Union);
        CHECK(c->GetLeft() == s1);
        CHECK(c->GetRight() == s2);
        CHECK(s1->GetParent().lock() == c);
        CHECK(s2->GetParent().lock() == c);
      }
    }
  }
}

SCENARIO("Evaluating the rule for a CSG operation")
{

  /// -----------------------------------------------------------------------
  /// @subsection Example Test Data
  struct TestData
  {
    CSGOperation op;
    bool lhit;
    bool inl;
    bool inr;
    bool result;
  };

  const std::array<TestData, 24> testData{ {
    // Union Rules
    { CSGOperation::Union, true, true, true, false },
    { CSGOperation::Union, true, true, false, true },
    { CSGOperation::Union, true, false, true, false },
    { CSGOperation::Union, true, false, false, true },
    { CSGOperation::Union, false, true, true, false },
    { CSGOperation::Union, false, true, false, false },
    { CSGOperation::Union, false, false, true, true },
    { CSGOperation::Union, false, false, false, true },
    // Intersection Rules
    { CSGOperation::Intersection, true, true, true, true },
    { CSGOperation::Intersection, true, true, false, false },
    { CSGOperation::Intersection, true, false, true, true },
    { CSGOperation::Intersection, true, false, false, false },
    { CSGOperation::Intersection, false, true, true, true },
    { CSGOperation::Intersection, false, true, false, true },
    { CSGOperation::Intersection, false, false, true, false },
    { CSGOperation::Intersection, false, false, false, false },
    // Difference Rules
    { CSGOperation::Difference, true, true, true, false },
    { CSGOperation::Difference, true, true, false, true },
    { CSGOperation::Difference, true, false, true, false },
    { CSGOperation::Difference, true, false, false, true },
    { CSGOperation::Difference, false, true, true, true },
    { CSGOperation::Difference, false, true, false, true },
    { CSGOperation::Difference, false, false, true, false },
    { CSGOperation::Difference, false, false, false, false },
  } };
  /// -----------------------------------------------------------------------

  WHEN("result = intersection_allowed(<op>, <lhit>, <inl>, <inr>)")
  {
    THEN("result == <result>")
    {
      for (const auto& [op, lhit, inl, inr, result] : testData) {
        CHECK(intersection_allowed(op, lhit, inl, inr) == result);
      }
    }
  }
}

SCENARIO("Filtering a list of intersections")
{

  /// -----------------------------------------------------------------------
  /// @subsection Example Test Data
  struct TestData
  {
    CSGOperation op;
    int x0;
    int x1;
  };

  const std::array<TestData, 3> testData{ {
    // Union Rules
    { CSGOperation::Union, 0, 3 },
    { CSGOperation::Intersection, 1, 2 },
    { CSGOperation::Difference, 0, 1 },
  } };
  /// -----------------------------------------------------------------------

  GIVEN("s1 = sphere()\
  \n\t s2 = cube()\
  \n\t And c = csg(<operation>, s1, s2)\
  \n\t And xs = intersections(1:s1, 2:s2, 3:s1, 4:s2)")
  {
    auto s1 = CreateShapeAs<Sphere>();
    auto s2 = CreateShapeAs<Cube>();

    WHEN("result = filter_interessctions(c, xs)")
    {
      THEN("result.count == 2\
      \n\t And result[0] == xs[<x0>]\
      \n\t And result[1] == xs[<x1>]")
      {
        for (const auto& [operation, x0, x1] : testData) {
          auto c = CreateCSGShape(operation, s1, s2);
          auto xs = Intersections{
            { 1, s1.get() }, { 2, s2.get() }, { 3, s1.get() }, { 4, s2.get() }
          };

          auto result = filter_intersections(*c.get(), xs);

          REQUIRE(result.Count() == 2);
          CHECK(result[0] == xs[x0]);
          CHECK(result[1] == xs[x1]);
        }
      }
    }
  }
}

SCENARIO("A ray misses a CSG object")
{
  GIVEN("c = csg('union', sphere(), cube())\
  \n\t And r = ray(point(0, 2, -5), vector(0, 0, 1))")
  {
    auto s1 = CreateShapeAs<Sphere>();
    auto s2 = CreateShapeAs<Cube>();
    auto c = CreateCSGShape(CSGOperation::Union, s1, s2);
    auto r = Ray{ Point(0, 2, -5), Vector(0, 0, 1) };

    WHEN("xs = local_intersect(c, r)")
    {
      auto xs = c->Intersect(r);

      THEN("xs is empty") { CHECK(xs.Count() == 0); }
    }
  }
}

SCENARIO("A ray hits a CSG object")
{
  GIVEN("s1 = sphere()\
  \n\t And s2 = sphere()\
  \n\t And set_transform(s2, translation(0, 0, 0.5))\
  \n c = csg('union', s1, s2)\
  \n\t And r = ray(point(0, 0, -5), vector(0, 0, 1))")
  {
    auto s1 = CreateShapeAs<Sphere>();
    auto s2 = CreateShapeAs<Sphere>();
    s2->SetTransform(translation(0, 0, 0.5));
    auto c = CreateCSGShape(CSGOperation::Union, s1, s2);
    auto r = Ray{ Point(0, 0, -5), Vector(0, 0, 1) };

    WHEN("xs = local_intersect(c, r)")
    {
      auto xs = c->Intersect(r);

      THEN("xs.count == 2\
      \n\t And xs[0].t == 4\
      \n\t And xs[0].object == s1\
      \n\t And xs[1].t == 6.5\
      \n\t And xs[1].object == s2")
      {
        REQUIRE(xs.Count() == 2);
        CHECK(xs[0].t == 4);
        CHECK(xs[0].object == s1.get());
        CHECK(xs[1].t == 6.5);
        CHECK(xs[1].object == s2.get());
      }
    }
  }
}
