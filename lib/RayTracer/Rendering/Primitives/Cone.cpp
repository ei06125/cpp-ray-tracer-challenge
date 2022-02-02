#include "RayTracer/Rendering/Primitives/Cone.hpp"

namespace RayTracer::Rendering::Primitives {
using namespace Math;

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------

Tuple Cone::GetNormalAt(Tuple point) const
{
  return GetLocalNormalAt(point);
}

float Cone::GetMinimum() const
{
  return m_Minimum;
}

float Cone::GetMaximum() const
{
  return m_Maximum;
}

bool Cone::IsClosed() const
{
  return m_Closed;
}

Tuple Cone::GetLocalNormalAt(Tuple point) const
{
  // compute the square of the distance from the y axis
  auto dist = (point.x * point.x) + (point.z * point.z);

  if (dist < 1 && point.y >= m_Maximum - EPSILON) {
    return make_vector(0, 1, 0);
  } else if (dist < 1 && point.y <= m_Minimum + EPSILON) {
    return make_vector(0, -1, 0);
  }
  return make_vector(point.x, 0, point.z);
}

Intersections Cone::VirtualIntersect(const Ray& r) const
{
  const auto o = r.origin;
  const auto d = r.direction;

  const auto a = (d.x * d.x) - (d.y * d.y) + (d.z * d.z);
  const auto b = (2 * o.x * d.x) - (2 * o.y * d.y) + (2 * o.z * d.z);
  auto c = (o.x * o.x) - (o.y * o.y) + (o.z * o.z);

  // ray is parallel to one of the cone's halves
  if (a == 0) {
    if (b == 0) {
      return {};
    }

    auto t = -c / (2 * b);
    return Intersections{ { t, this } };
  }

  Intersections xs{};
  auto disc = (b * b) - 4 * a * c;

  // ray does not intersect the cylinder
  if (disc < 0) {
    return {};
  }

  auto sqrtd = std::sqrt(disc);

  auto t0 = (-b - sqrtd) / (2 * a);
  auto t1 = (-b + sqrtd) / (2 * a);
  if (t0 > t1) {
    std::swap(t0, t1);
  }

  auto y0 = r.origin.y + t0 * r.direction.y;
  if (m_Minimum < y0 && y0 < m_Maximum) {
    xs.EmplaceBack(t0, this);
  }

  auto y1 = r.origin.y + t1 * r.direction.y;
  if (m_Minimum < y1 && y1 < m_Maximum) {
    xs.EmplaceBack(t1, this);
  }

  IntersectCaps(r, xs);

  return xs;
}

bool Cone::CheckCap(const Ray& r, float t) const
{
  auto x = r.origin.x + t * r.direction.x;
  auto z = r.origin.z + t * r.direction.z;

  return (x * x + z * z) <= 1;
}

void Cone::IntersectCaps(const Ray& r, Intersections& xs) const
{
  // caps only matter if the cylinder is closed, and might possibly be
  // intersected by the ray
  if (!m_Closed || r.direction.y == 0) {
    return;
  }

  // check for an intersection with the lower end cap by intersecting the ray
  // with the plane at y=cyl.minimum
  auto t = (m_Minimum - r.origin.y) / r.direction.y;
  if (CheckCap(r, t)) {
    xs.EmplaceBack(t, this);
  }

  // check for an intersection with the upper end cap by intersecting the ray
  // with the plane at y=cyl.maximum
  t = (m_Maximum - r.origin.y) / r.direction.y;
  if (CheckCap(r, t)) {
    xs.EmplaceBack(t, this);
  }
}

/// ---------------------------------------------------------------------------
/// @subsection Modifiers
/// ---------------------------------------------------------------------------

void Cone::SetMinimum(float newMinimum)
{
  m_Minimum = newMinimum;
}

void Cone::SetMaximum(float newMaximum)
{
  m_Maximum = newMaximum;
}

void Cone::SetClosed(bool newClosed)
{
  m_Closed = newClosed;
}

/// ===========================================================================
/// @section Non-member functions
/// ===========================================================================

} // namespace RayTracer::Rendering::Primitives
