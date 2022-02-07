#pragma once
#include "RayTracerPCH.hpp"

#include "RayTracer/Rendering/Lighting/Intersection.hpp"
#include "RayTracer/Rendering/Primitives/Shape.hpp"

namespace RayTracer {
namespace Rendering {
namespace Primitives {
using namespace Math;

enum class CSGOperation
{
  Union,
  Intersection,
  Difference
};

class CSG
  : public Shape
  , public std::enable_shared_from_this<CSG>
{
public:
  /// @section Member functions
  /// @subsection Special member functions
  CSG(CSGOperation op, const SharedShape& lhs, const SharedShape& rhs);

  /// @subsection Observers
  const CSGOperation& GetOperation() const;
  const SharedShape& GetLeft() const;
  const SharedShape& GetRight() const;

  /// @subsubsection Virtual member functions
  bool Contains(const Shape& shape) const override;

protected:
  Tuple GetLocalNormalAt(Tuple point,
                         const Intersection* i = nullptr) const override;
  Intersections GetLocalIntersect(const Ray& r) const override;

private:
  CSGOperation m_Operation;
  const SharedShape& m_Left;
  const SharedShape& m_Right;
};

/// @section Non-member functions

/// @subsection Creation methods
SharedPtr<CSG> CreateCSGShape(CSGOperation op,
                              const SharedShape& lhs,
                              const SharedShape& rhs);

/// @section Helper functions
/**
 * @param op is the CSG operation being evaluated
 * @param lhit is true if the left shape was hit, or false if right was hit
 * @param inl is true if the hit occurs inside the left shape
 * @param inr is true if the hit occurs inside the right shape
 */
bool intersection_allowed(CSGOperation op, bool lhit, bool inl, bool inr);


Intersections filter_intersections(const CSG& csg, const Intersections& xs);

} // namespace Primitives
} // namespace Rendering
} // namespace RayTracer
