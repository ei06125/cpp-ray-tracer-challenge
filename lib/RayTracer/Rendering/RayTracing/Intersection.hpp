#pragma once

#include "RayTracer/Rendering/RayTracing/Ray.hpp"

#include <memory>
#include <vector>

// Forward Declared to prevent cycles
class Shape;

/// ===========================================================================
/// @section Intersection
/// ===========================================================================

struct Intersection
{
  Intersection(float t_, const Shape* object_);

  float t;
  const Shape* object;

  bool operator<(const Intersection& rhs) const;
  bool operator==(const Intersection& rhs) const;
};

/// ===========================================================================
/// @section Intersections
/// ===========================================================================

class Intersections
{
public:
  Intersections();
  Intersections(std::initializer_list<Intersection> points);
  std::size_t Count() const;
  Intersection& operator[](std::size_t index);
  Intersection operator[](std::size_t index) const;

  template<typename... Args>
  void Add(Args&&... args)
  {
    intersectionPoints.emplace_back(args...);
  }

  std::vector<Intersection>& GetIntersectionPoints();

  Intersection* Hit();

private:
  std::vector<Intersection> intersectionPoints;
};
