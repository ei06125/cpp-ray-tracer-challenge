#pragma once

#include "RayTracer/Rendering/Primitives/Shape.hpp"
#include "RayTracer/Rendering/RayTracing/Intersection.hpp"

class Plane : public Shape
{
public:
  ~Plane() override;
  Plane();

  Tuple GetNormalAt(Tuple point) const override;
  // Intersections Intersect(const Ray& r) const override;

protected:
  Tuple GetLocalNormalAt(Tuple point) const override;
  Intersections VirtualIntersect(const Ray& r) const override;
};

inline bool operator==(const Shape& lhs, const Plane& rhs)
{
  return lhs == static_cast<const Shape&>(rhs);
}

inline bool operator==(const Shape* lhs, const Plane& rhs)
{
  return *lhs == static_cast<const Shape&>(rhs);
}
