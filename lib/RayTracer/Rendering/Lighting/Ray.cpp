#include "RayTracer/Rendering/Lighting/Ray.hpp"

namespace RayTracer {
namespace Rendering {
namespace Lighting {

using namespace Math;

Tuple position(const Ray& ray, float time)
{
  return ray.origin + ray.direction * time;
}

Ray transform(const Ray& r, const mat4& m)
{
  return { m * r.origin, m * r.direction };
}

} // namespace Lighting
} // namespace Rendering
} // namespace RayTracer
