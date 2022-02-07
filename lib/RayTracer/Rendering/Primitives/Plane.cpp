#include "RayTracer/Rendering/Primitives/Plane.hpp"

namespace RayTracer::Rendering::Primitives {
using namespace Math;

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------

Tuple Plane::GetLocalNormalAt(Tuple point, const Intersection*) const
{
  return Vector(0, 1, 0); // m_Transform * Vector(0, 1, 0);
}

Intersections Plane::GetLocalIntersect(const Ray& r) const
{
  if (std::abs(r.direction.y) < EPSILON) {
    return {};
  }
  return { -r.origin.y / r.direction.y, this };
}

} // namespace RayTracer::Rendering::Primitives
