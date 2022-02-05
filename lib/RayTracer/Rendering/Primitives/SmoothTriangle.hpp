#pragma once
#include "RayTracerPCH.hpp"

#include "RayTracer/Rendering/Primitives/Triangle.hpp"

namespace RayTracer {
namespace Rendering {
namespace Primitives {
using namespace Math;

class SmoothTriangle : public Triangle
{
public:
  /// @section Member functions
  /// @subsection Special member functions
  SmoothTriangle(Tuple P1, Tuple P2, Tuple P3, Tuple N1, Tuple N2, Tuple N3);

  /// @subsection Observers
  /// @subsection Modifiers

protected:
  Tuple GetLocalNormalAt(Tuple point, const Intersection* i) const override;
  Intersections MakeIntersections(float t, float u, float v) const override;

public:
  Tuple n1;
  Tuple n2;
  Tuple n3;
};

/// @section Non-member functions
bool operator==(const SmoothTriangle& lhs, const SmoothTriangle& rhs);

} // namespace Primitives
} // namespace Rendering
} // namespace RayTracer
