#include "RayTracer/Rendering/RayTracing/Intersection.hpp"

/// ===========================================================================
/// @section Intersection
/// ===========================================================================

Intersection::Intersection(float t_, Sphere object_)
  : t(t_)
  , object(std::move(object_))
{}

bool operator<(const Intersection& lhs, const Intersection& rhs)
{
  return lhs.t < rhs.t;
}

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

Intersection Intersections::operator[](std::size_t index) const
{
  assert(index >= 0 && index < intersectionPoints.size());
  return intersectionPoints[index];
}

void Intersections::Push(Intersection&& i)
{
  intersectionPoints.push_back(std::move(i));
}

std::vector<Intersection>& Intersections::GetIntersectionPoints()
{
  return intersectionPoints;
}

/// ===========================================================================
/// @section Functions
/// ===========================================================================

Intersections intersect(const Sphere& s, const Ray& r)
{
  Intersections result{};

  auto r2 = transform(r, inverse(s.transform));
  // the vector from the sphere's center, to the ray origin
  // remember: the sphere is centered at the world origin
  auto sphere_to_ray = r2.origin - make_point(0, 0, 0);

  auto a = dot(r2.direction, r2.direction);
  auto b = 2 * dot(r2.direction, sphere_to_ray);
  auto c = dot(sphere_to_ray, sphere_to_ray) - 1;

  auto discriminant = (b * b) - (4 * a * c);
  if (discriminant < 0) {
    return result;
  }

  auto t1 = (-b - std::sqrt(discriminant)) / (2 * a);
  auto t2 = (-b + std::sqrt(discriminant)) / (2 * a);

  result.Push({ t1, s });
  result.Push({ t2, s });

  return result;
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

Computations prepare_computations(const Intersection& i, const Ray& r)
{
  auto point = position(r, i.t);
  auto eyev = -r.direction;
  auto normalv = normal_at(i.object, point);

  Computations comps{ i.t, i.object, point, eyev, normalv, point };

  if (dot(comps.normalv, comps.eyev) < 0) {
    comps.inside = true;
    comps.normalv = -comps.normalv;
  } else {
    comps.inside = false;
  }

  comps.over_point = comps.point + comps.normalv * EPSILON;

  return comps;
}
