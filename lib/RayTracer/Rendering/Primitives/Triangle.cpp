#include "RayTracer/Rendering/Primitives/Triangle.hpp"

namespace RayTracer::Rendering::Primitives {
using namespace Math;

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

/// ---------------------------------------------------------------------------
/// @subsection Special member functions
/// ---------------------------------------------------------------------------
Triangle::Triangle(Tuple aP1, Tuple aP2, Tuple aP3)
  : p1(aP1)
  , p2(aP2)
  , p3(aP3)
  , e1(p2 - p1)
  , e2(p3 - p1)
  , normal(normalize(cross(e2, e1)))
{}

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------

Tuple Triangle::GetLocalNormalAt(Tuple point, const Intersection*) const
{
  return normal;
}

Intersections Triangle::GetLocalIntersect(const Ray& r) const
{
  auto dir_cross_e2 = cross(r.direction, e2);
  auto det = dot(e1, dir_cross_e2);
  if (std::abs(det) < EPSILON) {
    return {};
  }

  auto f = 1.0f / det;

  auto p1_to_origin = r.origin - p1;
  auto u = f * dot(p1_to_origin, dir_cross_e2);
  if (u < 0 || u > 1) {
    return {};
  }

  auto origin_cross_e1 = cross(p1_to_origin, e1);
  auto v = f * dot(r.direction, origin_cross_e1);
  if (v < 0 || (u + v) > 1) {
    return {};
  }

  auto t = f * dot(e2, origin_cross_e1);
  return MakeIntersections(t, u, v);
}

Intersections Triangle::MakeIntersections(float t, float u, float v) const
{
  return Intersections{ { t, this } };
}

/// ===========================================================================
/// @section Non-member functions
/// ===========================================================================

bool operator==(const Triangle& lhs, const Triangle& rhs)
{
  return lhs.p1 == rhs.p1 && lhs.p2 == rhs.p2 && lhs.p3 == rhs.p3 &&
         lhs.e1 == rhs.e1 && lhs.e2 == rhs.e2 && lhs.normal == rhs.normal;
}

} // namespace RayTracer::Rendering::Primitives
