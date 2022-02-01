#include "RayTracer/Rendering/Primitives/Sphere.hpp"

namespace RayTracer::Rendering::Primitives {
using namespace Math;

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

Sphere::~Sphere() = default;
Sphere::Sphere()
  : Shape()
  , m_Radius(1.0f)
{}
Sphere::Sphere(const Sphere& other) = default;
Sphere::Sphere(Sphere&& other) noexcept = default;
Sphere& Sphere::operator=(const Sphere& other) = default;
Sphere& Sphere::operator=(Sphere&& other) noexcept = default;

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
