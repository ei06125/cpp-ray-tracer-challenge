#include "RayTracer/Rendering/RayTracing/Sphere.hpp"

std::size_t Sphere::SphereID = 0;

Sphere::Sphere()
  : transform(mat4::Identity())
  , material(Material())
  , origin(make_point(0, 0, 0))
  , radius(1.0f)
  , id(SphereID++)
{}

bool operator==(const Sphere& lhs, const Sphere& rhs)
{
  return lhs.transform == rhs.transform && lhs.material == rhs.material &&
         lhs.origin == rhs.origin && lhs.radius == rhs.radius;
}

void set_transform(Sphere& s, mat4 t)
{
  s.transform = t;
}

Tuple normal_at(const Sphere& s, const Tuple& world_point)
{
  auto object_point = inverse(s.transform) * world_point;
  auto object_normal = object_point - make_point(0, 0, 0);
  auto world_normal = transpose(inverse(s.transform)) * object_normal;
  world_normal.w = 0;
  return normalize(world_normal);
}
