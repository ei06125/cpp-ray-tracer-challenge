#include "RayTracer/Rendering/Primitives/Cube.hpp"

namespace RayTracer::Rendering::Primitives {
using namespace Math;

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------

Tuple Cube::GetLocalNormalAt(Tuple point, const Intersection*) const
{
  auto maxc =
    std::max(std::abs(point.x), std::max(std::abs(point.y), std::abs(point.z)));

  if (maxc == std::abs(point.x)) {
    return Vector(point.x, 0, 0);
  } else if (maxc == std::abs(point.y)) {
    return Vector(0, point.y, 0);
  }
  return Vector(0, 0, point.z);
}

Intersections Cube::GetLocalIntersect(const Ray& r) const
{
  auto [xtmin, xtmax] = check_axis(r.origin.x, r.direction.x);
  auto [ytmin, ytmax] = check_axis(r.origin.y, r.direction.y);
  auto [ztmin, ztmax] = check_axis(r.origin.z, r.direction.z);

  auto tmin = std::max(xtmin, std::max(ytmin, ztmin));
  auto tmax = std::min(xtmax, std::min(ytmax, ztmax));

  if (tmin > tmax) {
    return {};
  }

  return Intersections{ { tmin, this }, { tmax, this } };
}

/// ===========================================================================
/// @section Non-member functions
/// ===========================================================================

std::tuple<float, float> check_axis(float origin, float direction)
{
  auto tmin_numerator = (-1 - origin);
  auto tmax_numerator = (1 - origin);

  auto tmin = tmin_numerator * INFINITY;
  auto tmax = tmax_numerator * INFINITY;
  if (std::abs(direction) >= EPSILON) {
    tmin = tmin_numerator / direction;
    tmax = tmax_numerator / direction;
  }

  if (tmin > tmax) {
    std::swap(tmin, tmax);
  }

  return { tmin, tmax };
}

} // namespace RayTracer::Rendering::Primitives
