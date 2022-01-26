#include "RayTracer/Rendering/Primitives/Sphere.hpp"

namespace RayTracer::Rendering::Primitives {
using namespace Math;

Sphere::~Sphere() = default;

Sphere::Sphere()
  : Shape()
  , m_Radius(1.0f)
{}

float Sphere::GetRadius() const
{
  return m_Radius;
}

void Sphere::SetRadius(float newRadius)
{
  m_Radius = newRadius;
}

bool Sphere::operator==(const Sphere& rhs) const
{
  return m_Radius == rhs.m_Radius &&
         static_cast<const Shape&>(*this) == static_cast<const Shape&>(rhs);
}

Tuple Sphere::GetLocalNormalAt(Tuple localPoint) const
{
  return (localPoint - make_point(0, 0, 0));
}

Intersections Sphere::VirtualIntersect(const Ray& r) const
{
  Intersections result{};

  // the vector from the sphere's center, to the ray origin
  // remember: the sphere is centered at the world origin
  auto sphere_to_ray = r.origin - make_point(0, 0, 0);

  auto a = dot(r.direction, r.direction);
  auto b = 2 * dot(r.direction, sphere_to_ray);
  auto c = dot(sphere_to_ray, sphere_to_ray) - 1;

  auto discriminant = (b * b) - (4 * a * c);
  if (discriminant < 0) {
    return result;
  }

  auto t1 = (-b - std::sqrt(discriminant)) / (2 * a);
  auto t2 = (-b + std::sqrt(discriminant)) / (2 * a);

  result.Add(t1, this);
  result.Add(t2, this);

  return result;
}

} // namespace RayTracer::Rendering::Primitives