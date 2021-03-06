#include "RayTracer/Rendering/Primitives/Group.hpp"

namespace RayTracer::Rendering::Primitives {
using namespace Math;

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------

bool Group::IsEmpty() const
{
  return m_Children.empty();
}

bool Group::Contains(const Shape& shape) const
{
  for (const auto& child : m_Children) {
    if (child->Contains(shape)) {
      return true;
    }
  }
  return false;
}

///
/// @subsubsection Virtual member functions
///

Tuple Group::GetLocalNormalAt(Tuple point, const Intersection*) const
{
  return Point(0, 0, 1);
}

Intersections Group::GetLocalIntersect(const Ray& r) const
{
  Intersections xs{};
  for (auto child : m_Children) {
    auto childXS = child->Intersect(r);
    auto childPoints = childXS.GetIntersectionPoints();
    for (auto point : childPoints) {
      xs.Add(point);
    }
  }
  xs.Sort();
  return xs;
}

/// ---------------------------------------------------------------------------
/// @subsection Modifiers
/// ---------------------------------------------------------------------------

void Group::AddChild(std::shared_ptr<Shape> newChild)
{
  newChild->SetParent(shared_from_this());
  m_Children.insert(newChild);
}

} // namespace RayTracer::Rendering::Primitives
