#include "RayTracer/Rendering/Primitives/Sphere.hpp"

namespace RayTracer::Rendering::Primitives {
using namespace Math;

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------

float Sphere::GetRadius() const
{
  return m_Radius;
}

/// ---------------------------------------------------------------------------
/// @subsection Modifiers
/// ---------------------------------------------------------------------------

void Sphere::SetRadius(float newRadius)
{
  m_Radius = newRadius;
}

/// ===========================================================================
/// @section Virtual functions
/// ===========================================================================

Tuple Sphere::GetLocalNormalAt(Tuple localPoint, const Intersection*) const
{
  return (localPoint - Point(0, 0, 0));
}

Intersections Sphere::GetLocalIntersect(const Ray& r) const
{
  Intersections result{};

  // the vector from the sphere's center, to the ray origin
  // remember: the sphere is centered at the world origin
  auto sphere_to_ray = r.origin - Point(0, 0, 0);

  auto a = dot(r.direction, r.direction);
  auto b = 2 * dot(r.direction, sphere_to_ray);
  auto c = dot(sphere_to_ray, sphere_to_ray) - 1;

  auto discriminant = (b * b) - (4 * a * c);
  if (discriminant < 0) {
    return result;
  }

  auto sqrtd = std::sqrt(discriminant);
  auto t1 = (-b - sqrtd) / (2 * a);
  auto t2 = (-b + sqrtd) / (2 * a);

  result.EmplaceBack(t1, this);
  result.EmplaceBack(t2, this);

  return result;
}

/// ===========================================================================
/// @section Non-member functions
/// ===========================================================================

bool operator==(const Sphere& lhs, const Sphere& rhs)
{
  return lhs.m_Radius == rhs.m_Radius &&
         static_cast<const Shape&>(lhs) == static_cast<const Shape&>(rhs);
}

/// ---------------------------------------------------------------------------
/// @subsection Creation methods
/// ---------------------------------------------------------------------------

Sphere GlassSphere()
{
  Sphere s;
  s.SetMaterial().transparency = 1.0;
  s.SetMaterial().refractiveIndex = 1.5;
  return s;
}

} // namespace RayTracer::Rendering::Primitives
