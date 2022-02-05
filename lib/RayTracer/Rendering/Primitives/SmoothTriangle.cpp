#include "RayTracer/Rendering/Primitives/SmoothTriangle.hpp"

#include "RayTracer/Core/Assertions.hpp"

namespace RayTracer::Rendering::Primitives {
using namespace Math;

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

/// ---------------------------------------------------------------------------
/// @subsection Special member functions
/// ---------------------------------------------------------------------------
SmoothTriangle::SmoothTriangle(Tuple P1,
                               Tuple P2,
                               Tuple P3,
                               Tuple N1,
                               Tuple N2,
                               Tuple N3)
  : Triangle(P1, P2, P3)
  , n1(N1)
  , n2(N2)
  , n3(N3)
{}

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------

Tuple SmoothTriangle::GetLocalNormalAt(Tuple point,
                                       const Intersection* hit) const
{
  DEBUG_ASSERT(hit != nullptr);
  return (n2 * hit->u) + (n3 * hit->v) + (n1 * (1 - hit->u - hit->v));
}

Intersections SmoothTriangle::MakeIntersections(float t, float u, float v) const
{
  return Intersections{ { t, this, u, v } };
}

/// ===========================================================================
/// @section Non-member functions
/// ===========================================================================

bool operator==(const SmoothTriangle& lhs, const SmoothTriangle& rhs)
{
  return static_cast<const Triangle&>(lhs) ==
           static_cast<const Triangle&>(rhs) &&
         lhs.n1 == rhs.n1 && lhs.n2 == rhs.n2 && lhs.n3 == rhs.n3;
}

} // namespace RayTracer::Rendering::Primitives
