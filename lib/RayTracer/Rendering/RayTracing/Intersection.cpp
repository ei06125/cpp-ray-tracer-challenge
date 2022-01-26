#include "RayTracer/Rendering/RayTracing/Intersection.hpp"

/// ===========================================================================
/// @section Intersection
/// ===========================================================================

Intersection::Intersection(float t_, const Shape* object_)
  : t(t_)
  , object(object_)
{}

bool Intersection::operator<(const Intersection& rhs) const
{
  return t < rhs.t;
}

bool Intersection::operator==(const Intersection& rhs) const
{
  return t == rhs.t && object == rhs.object;
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

std::vector<Intersection>& Intersections::GetIntersectionPoints()
{
  return intersectionPoints;
}

/// ===========================================================================
/// @section Functions
/// ===========================================================================

Intersection* Intersections::Hit()
{
  Intersection* result = nullptr;

  // TODO: check this algorithm (simplify!)
  std::size_t start = 0;
  for (; start < Count(); ++start) {
    if (intersectionPoints[start].t >= 0) {
      result = &intersectionPoints[start++];
      break;
    }
  }
  for (; start < Count(); ++start) {
    if (intersectionPoints[start].t >= 0 &&
        intersectionPoints[start].t < result->t) {
      result = &intersectionPoints[start];
    }
  }

  return result;
}
