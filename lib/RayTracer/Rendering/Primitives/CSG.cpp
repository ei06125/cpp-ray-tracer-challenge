#include "RayTracer/Rendering/Primitives/CSG.hpp"

namespace RayTracer::Rendering::Primitives {
using namespace Math;

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

CSG::CSG(CSGOperation op, const SharedShape& lhs, const SharedShape& rhs)
  : Shape()
  , m_Operation(op)
  , m_Left(lhs)
  , m_Right(rhs)
{}

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------

const CSGOperation& CSG::GetOperation() const
{
  return m_Operation;
}

const SharedShape& CSG::GetLeft() const
{
  return m_Left;
}

const SharedShape& CSG::GetRight() const
{
  return m_Right;
}

///
/// @subsubsection Virtual member functions
///

bool CSG::Contains(const Shape& shape) const
{
  if (m_Left->Contains(shape) || m_Right->Contains(shape)) {
    return true;
  }
  return false;
}

Tuple CSG::GetLocalNormalAt(Tuple point, const Intersection*) const
{
  return Point(0, 0, 1);
}

Intersections CSG::GetLocalIntersect(const Ray& r) const
{
  auto leftXS = m_Left->Intersect(r);
  auto rightXS = m_Right->Intersect(r);

  Intersections xs(leftXS);
  for (auto intersection : rightXS.GetIntersectionPoints()) {
    xs.Add(std::move(intersection));
  }
  xs.Sort();
  auto result = filter_intersections(*this, xs);
  return result;
}

/// ---------------------------------------------------------------------------
/// @subsection Modifiers
/// ---------------------------------------------------------------------------

/// ===========================================================================
/// @section Non-member functions
/// ===========================================================================

/// ---------------------------------------------------------------------------
/// @subsection Creation methods
/// ---------------------------------------------------------------------------

SharedPtr<CSG> CreateCSGShape(CSGOperation op,
                              const SharedShape& lhs,
                              const SharedShape& rhs)
{
  auto parent = std::make_shared<CSG>(op, lhs, rhs);
  lhs->SetParent(parent);
  rhs->SetParent(parent);
  return parent;
}

/// ---------------------------------------------------------------------------
/// @subsection Helper functions
/// ---------------------------------------------------------------------------

bool intersection_allowed(CSGOperation op, bool lhit, bool inl, bool inr)
{
  switch (op) {
    case CSGOperation::Union:
      return (lhit && !inr) || (!lhit && !inl);
    case CSGOperation::Intersection:
      return (lhit && inr) || (!lhit && inl);
    case CSGOperation::Difference:
      return (lhit && !inr) || (!lhit && inl);
    default:
      return false;
  }
}

Intersections filter_intersections(const CSG& csg, const Intersections& xs)
{
  // begin outside of both children
  bool inl{ false }; // true if the hit occurs inside the left shape
  bool inr{ false }; // true if the hit occurs inside the right shape

  // prepare a list to receive the filtered intersections
  Intersections result{};

  for (const auto& intersection : xs.GetIntersectionPoints()) {
    auto lhit = csg.GetLeft()->Contains(*intersection.object);

    if (intersection_allowed(csg.GetOperation(), lhit, inl, inr)) {
      result.Add(intersection);
    }

    // depending on whihch object was hit, toggle either inl or inr
    if (lhit) {
      inl = !inl;
    } else {
      inr = !inr;
    }
  }

  return result;
}

} // namespace RayTracer::Rendering::Primitives
