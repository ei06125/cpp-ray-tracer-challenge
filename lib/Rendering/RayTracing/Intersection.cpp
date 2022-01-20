#include "Rendering/RayTracing/Intersection.hpp"

#include <cassert>
#include <cmath>

/// ===========================================================================
/// @section Intersection
/// ===========================================================================

Intersection::Intersection(float t_, const Sphere& object_)
  : t(t_)
  , object(object_)
{}

bool operator==(const Intersection& lhs, const Intersection& rhs)
{
  return lhs.object == rhs.object && lhs.t == rhs.t;
}

/// ===========================================================================
/// @section Intersections
/// ===========================================================================

Intersections::Intersections() = default;

Intersections::Intersections(std::initializer_list<Intersection> points)
  : intersectionPoints(points)
{}

std::size_t Intersections::Count() const
{
  return intersectionPoints.size();
}

Intersection& Intersections::operator[](std::size_t index)
{
  assert(index >= 0 && index < intersectionPoints.size());
  return intersectionPoints[index];
}

/// ===========================================================================
/// @section Functions
/// ===========================================================================

Intersections intersect(const Sphere& s, const Ray& r)
{
  auto r2 = transform(r, inverse(s.transform));
  // the vector from the sphere's center, to the ray origin
  // remember: the sphere is centered at the world origin
  auto sphere_to_ray = r2.origin - make_point(0, 0, 0);

  auto a = dot(r2.direction, r2.direction);
  auto b = 2 * dot(r2.direction, sphere_to_ray);
  auto c = dot(sphere_to_ray, sphere_to_ray) - 1;

  auto discriminant = (b * b) - (4 * a * c);
  if (discriminant < 0) {
    return {};
  }

  auto t1 = (-b - std::sqrt(discriminant)) / (2 * a);
  auto t2 = (-b + std::sqrt(discriminant)) / (2 * a);

  return { { { t1, s }, { t2, s } } };
}

Intersection* hit(Intersections& xs)
{
  Intersection* result = nullptr;
  std::size_t start = 0;
  for (; start < xs.Count(); ++start) {
    if (xs[start].t >= 0) {
      result = &xs[start++];
      break;
    }
  }
  for (; start < xs.Count(); ++start) {
    if (xs[start].t >= 0 && xs[start].t < result->t) {
      result = &xs[start];
    }
  }
  return result;
}
