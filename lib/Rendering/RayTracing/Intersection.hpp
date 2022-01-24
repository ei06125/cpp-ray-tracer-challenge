#pragma once
#include <vector>

#include "Rendering/RayTracing/Ray.hpp"
#include "Rendering/RayTracing/Sphere.hpp"

/// ===========================================================================
/// @section Intersection
/// ===========================================================================

struct Intersection
{
  Intersection(float t_, Sphere sphere_);

  float t;
  Sphere object;
};

bool operator<(const Intersection& lhs, const Intersection& rhs);
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
  Intersection operator[](std::size_t index) const;
  void Push(Intersection&& i);

  std::vector<Intersection>& GetIntersectionPoints();

private:
  std::vector<Intersection> intersectionPoints;
};

/// ===========================================================================
/// @section Computations
/// ===========================================================================

struct Computations
{
  float t;
  Sphere object;
  Tuple point;
  Tuple eyev;
  Tuple normalv;
  Tuple over_point;
  bool inside;
};

/// ===========================================================================
/// @section Functions
/// ===========================================================================

Intersections intersect(const Sphere& s, const Ray& r);
Intersection* hit(Intersections& xs);
Computations prepare_computations(const Intersection& i, const Ray& r);
