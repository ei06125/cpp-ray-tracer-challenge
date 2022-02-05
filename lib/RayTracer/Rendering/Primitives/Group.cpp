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

bool Group::Contains(const std::shared_ptr<Shape>& shape) const
{
  return m_Children.contains(shape);
}

///
/// @subsubsection Virtual member functions
///

Tuple Group::GetLocalNormalAt(Tuple point, const Intersection*) const
{
  return make_point(0, 0, 1);
}

Intersections Group::VirtualIntersect(const Ray& r) const
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
