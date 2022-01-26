#include "RayTracer/Rendering/Primitives/Plane.hpp"

namespace RayTracer::Rendering::Primitives {
using namespace Math;

Plane::~Plane() = default;
Plane::Plane() = default;

Tuple Plane::GetNormalAt(Tuple point) const
{
  return GetLocalNormalAt(point);
}

Tuple Plane::GetLocalNormalAt(Tuple point) const
{
  return make_vector(0, 1, 0);
}

Intersections Plane::VirtualIntersect(const Ray& r) const
{
  if (std::abs(r.direction.y) < EPSILON) {
    return {};
  }

  auto t = -r.origin.y / r.direction.y;

  Intersections result{};
  result.Add(t, this);
  return result;
}

} // namespace RayTracer::Rendering::Primitives