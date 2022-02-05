#pragma once
#include "RayTracerPCH.hpp"

#include "RayTracer/Rendering/Primitives/Shape.hpp"

namespace RayTracer {
namespace Rendering {
namespace Primitives {
using namespace Math;

class Triangle : public Shape
{
public:
  /// @section Member functions
  /// @subsection Special member functions
  Triangle(Tuple p1, Tuple p2, Tuple p3);

  /// @subsection Observers
  /// @subsection Modifiers

protected:
  Tuple GetLocalNormalAt(Tuple point, const Intersection*) const override;
  Intersections VirtualIntersect(const Ray& r) const override;

  virtual Intersections MakeIntersections(float t, float u, float v) const;

public:
  Tuple p1;
  Tuple p2;
  Tuple p3;

  Tuple e1; // edge vector
  Tuple e2; // edge vector

  Tuple normal;
};

/// @section Non-member functions

bool operator==(const Triangle& lhs, const Triangle& rhs);

} // namespace Primitives
} // namespace Rendering
} // namespace RayTracer
