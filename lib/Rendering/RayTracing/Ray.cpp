#include "Rendering/RayTracing/Ray.hpp"

Tuple position(const Ray& ray, float time)
{
  return ray.origin + ray.direction * time;
}

Ray transform(const Ray& r, const mat4& m)
{
  return { m * r.origin, m * r.direction };
}
