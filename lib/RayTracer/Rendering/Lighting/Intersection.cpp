#include "RayTracer/Rendering/Lighting/Intersection.hpp"

#include <cstdio>

namespace RayTracer {
namespace Rendering {
namespace Lighting {

using namespace Math;

/// ===========================================================================
/// @section Intersection
/// ===========================================================================

/// ---------------------------------------------------------------------------
/// @subsection Member functions
/// ---------------------------------------------------------------------------

Intersection::Intersection() = default;
Intersection::Intersection(float t_, const Shape* object_)
  : t(t_)
  , object(object_)
{}
Intersection::Intersection(const Intersection& other) = default;
Intersection::Intersection(Intersection&& other) noexcept = default;
Intersection::~Intersection() = default;
Intersection& Intersection::operator=(const Intersection& other) = default;
Intersection& Intersection::operator=(Intersection&& other) noexcept = default;

/// ---------------------------------------------------------------------------
/// @subsection Non-member functions
/// ---------------------------------------------------------------------------

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

/// ---------------------------------------------------------------------------
/// @subsection Member functions
/// ---------------------------------------------------------------------------

Intersections::Intersections() = default;
Intersections::Intersections(std::initializer_list<Intersection> points)
  : intersectionPoints(points)
{}
Intersections::Intersections(float t, const Shape* shapePtr)
  : intersectionPoints()
{
  intersectionPoints.emplace_back(t, shapePtr);
}
Intersections::Intersections(const Intersections& other) = default;
Intersections::Intersections(Intersections&& other) = default;
Intersections::~Intersections() = default;
Intersections& Intersections::operator=(const Intersections& other) = default;
Intersections& Intersections::operator=(Intersections&& other) = default;

/// ---------------------------------------------------------------------------
/// @subsubsection Element access
/// ---------------------------------------------------------------------------
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

/// ---------------------------------------------------------------------------
/// @subsubsection Capacity
/// ---------------------------------------------------------------------------

std::size_t Intersections::Count() const
{
  return intersectionPoints.size();
}

void Intersections::Reserve(std::size_t newCapacity)
{
  intersectionPoints.reserve(newCapacity);
}

void Intersections::Sort()
{
  std::sort(intersectionPoints.begin(), intersectionPoints.end());
}

/// ---------------------------------------------------------------------------
/// @subsubsection Observers
/// ---------------------------------------------------------------------------

std::vector<Intersection>& Intersections::Data()
{
  return intersectionPoints;
}

/// ===========================================================================
/// @section Functions
/// ===========================================================================

const Intersection* Intersections::Hit() const
{
  const Intersection* result = nullptr;

  // NOTE: basic benchmark tells two loops is faster
  // first loop gets result to non-nullptr
  std::size_t start = 0;
  for (; start < Count(); ++start) {
    if (intersectionPoints[start].t >= 0) {
      result = &intersectionPoints[start++];
      break;
    }
  }
  // second loop completes the search
  for (; start < Count(); ++start) {
    if (intersectionPoints[start].t >= 0 &&
        intersectionPoints[start].t < result->t) {
      result = &intersectionPoints[start];
    }
  }

  return result;
}

} // namespace Lighting
} // namespace Rendering
} // namespace RayTracer
