// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

using namespace RayTracer::Math;
using namespace RayTracer::Rendering::Primitives;

/// ---------------------------------------------------------------------------

/// ---------------------------------------------------------------------------

SCENARIO("Creating a bounding box for a normal sphere")
{
  GIVEN("s = sphere()")
  {
    auto s = std::make_shared<Sphere>();

    WHEN("b = bounding_box(s)")
    {
      auto b = std::make_shared<BoundingBox>(s);

      THEN("s.minimum == point(-1, -1, -1)\
            \n\t And s.maximum == point(1, 1, 1)")
      {
        CHECK(b->GetMinimum() == make_point(-1, -1, -1));
        CHECK(b->GetMaximum() == make_point(1, 1, 1));
      }
    }
  }
}

// SCENARIO("Creating a bounding box for a normal cube")
// {
//   GIVEN("c = cube()")
//   {
//     auto c = std::make_shared<Cube>();

//     WHEN("b = bounding_box(s)")
//     {
//       auto b = std::make_shared<BoundingBox>(c);

//       THEN("s.minimum == point(-1, -1, -1)\
//             \n\t And s.maximum == point(1, 1, 1)")
//       {
//         // CHECK(b->GetMinimum() == make_point(-1, -1, -1));
//         // CHECK(b->GetMaximum() == make_point(1, 1, 1));
//       }
//     }
//   }
// }

// SCENARIO("Creating a bounding box for a plane")
// {
//   GIVEN("p = plane()")
//   {
//     auto p = std::make_shared<Plane>();

//     WHEN("b = bounding_box(s)")
//     {
//       auto b = std::make_shared<BoundingBox>(p);

//       THEN("s.minimum == point(-1, -1, -1)\
//             \n\t And s.maximum == point(1, 1, 1)")
//       {
//         // CHECK(b->GetMinimum() == make_point(-1, -1, -1));
//         // CHECK(b->GetMaximum() == make_point(1, 1, 1));
//       }
//     }
//   }
// }

// SCENARIO("Creating a bounding box for an untruncated cylinder")
// {
//   GIVEN("cyl = cylinder()")
//   {
//     auto cyl = std::make_shared<Cylinder>();

//     WHEN("b = bounding_box(s)")
//     {
//       auto b = std::make_shared<BoundingBox>(cyl);

//       THEN("s.minimum == point(-1, -1, -1)\
//             \n\t And s.maximum == point(1, 1, 1)")
//       {
//         // CHECK(b->GetMinimum() == make_point(-1, -1, -1));
//         // CHECK(b->GetMaximum() == make_point(1, 1, 1));
//       }
//     }
//   }
// }

// SCENARIO("Creating a bounding box for group of shapes")
// {
//   GIVEN("g = group()")
//   {
//     auto g = std::make_shared<Group>();

//     WHEN("b = bounding_box(s)")
//     {
//       auto b = std::make_shared<BoundingBox>(g);

//       THEN("s.minimum == point(-1, -1, -1)\
//             \n\t And s.maximum == point(1, 1, 1)")
//       {
//         // CHECK(b->GetMinimum() == make_point(-1, -1, -1));
//         // CHECK(b->GetMaximum() == make_point(1, 1, 1));
//       }
//     }
//   }
// }
