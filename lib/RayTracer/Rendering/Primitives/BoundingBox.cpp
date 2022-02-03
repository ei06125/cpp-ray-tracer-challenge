#include "RayTracer/Rendering/Primitives/BoundingBox.hpp"

#include "RayTracer/Rendering/Primitives/Group.hpp"

namespace RayTracer::Rendering::Primitives {
using namespace Math;

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

/// ---------------------------------------------------------------------------
/// @subsection Special member functions
/// ---------------------------------------------------------------------------

BoundingBox::BoundingBox(const std::shared_ptr<Shape>& shape)
  : m_Minimum(make_point(0, 0, 0))
  , m_Maximum(make_point(0, 0, 0))
{}

BoundingBox::BoundingBox(const std::shared_ptr<Group>& group)
  : m_Minimum(make_point(0, 0, 0))
  , m_Maximum(make_point(0, 0, 0))
{}

// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------

Tuple BoundingBox::GetMinimum() const
{
  return m_Minimum;
}

Tuple BoundingBox::GetMaximum() const
{
  return m_Maximum;
}

///
/// @subsubsection Virtual member functions
///

Tuple BoundingBox::GetLocalNormalAt(Tuple point) const
{
  return make_point(0, 0, 1);
}

Intersections BoundingBox::VirtualIntersect(const Ray& r) const
{

  auto [xtmin, xtmax] = check_axis(r.origin.x, r.direction.x);
  auto [ytmin, ytmax] = check_axis(r.origin.y, r.direction.y);
  auto [ztmin, ztmax] = check_axis(r.origin.z, r.direction.z);

  auto tmin = std::max(xtmin, std::max(ytmin, ztmin));
  auto tmax = std::min(xtmax, std::min(ytmax, ztmax));

  //   if (tmin > tmax) {
  return {};
  //   }
}

/// ===========================================================================
/// @section Non-member functions
/// ===========================================================================

} // namespace RayTracer::Rendering::Primitives
