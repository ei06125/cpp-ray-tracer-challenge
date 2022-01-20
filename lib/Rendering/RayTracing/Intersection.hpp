#pragma once
#include <vector>

#include "Rendering/RayTracing/Ray.hpp"
#include "Rendering/RayTracing/Sphere.hpp"

/// ===========================================================================
/// @section Intersection
/// ===========================================================================

struct Intersection
{
  Intersection(float t_, const Sphere& sphere_);

  float t;
  const Sphere& object;
};

bool operator==(const Intersection& lhs, const Intersection& rhs);

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

private:
  std::vector<Intersection> intersectionPoints;
};

/// ===========================================================================
/// @section Functions
/// ===========================================================================

Intersections intersect(const Sphere& s, const Ray& r);
Intersection* hit(Intersections& xs);
