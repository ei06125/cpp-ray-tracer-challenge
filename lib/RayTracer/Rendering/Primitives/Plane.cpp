#include "RayTracer/Rendering/Primitives/Plane.hpp"

namespace RayTracer::Rendering::Primitives {
using namespace Math;

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

Plane::~Plane() = default;
Plane::Plane() = default;
Plane::Plane(const Plane& other) = default;
Plane::Plane(Plane&& other) noexcept = default;
Plane& Plane::operator=(const Plane& other) = default;
Plane& Plane::operator=(Plane&& other) noexcept = default;

/// ---------------------------------------------------------------------------
/// @subsection
/// ---------------------------------------------------------------------------

Tuple Plane::GetLocalNormalAt(Tuple point, const Intersection*) const
{
  return make_vector(0, 1, 0); // m_Transform * make_vector(0, 1, 0);
}

Intersections Plane::VirtualIntersect(const Ray& r) const
{
  if (std::abs(r.direction.y) < EPSILON) {
    return {};
  }
  return { -r.origin.y / r.direction.y, this };
}

} // namespace RayTracer::Rendering::Primitives
