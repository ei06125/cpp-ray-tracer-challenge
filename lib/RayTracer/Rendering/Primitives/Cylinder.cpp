#include "RayTracer/Rendering/Primitives/Cylinder.hpp"

namespace RayTracer::Rendering::Primitives {
using namespace Math;

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------

float Cylinder::GetMinimum() const
{
  return m_Minimum;
}

float Cylinder::GetMaximum() const
{
  return m_Maximum;
}

bool Cylinder::IsClosed() const
{
  return m_Closed;
}

Tuple Cylinder::GetLocalNormalAt(Tuple point, const Intersection*) const
{
  // compute the square of the distance from the y axis
  auto dist = (point.x * point.x) + (point.z * point.z);

  if (dist < 1 && point.y >= m_Maximum - EPSILON) {
    return Vector(0, 1, 0);
  } else if (dist < 1 && point.y <= m_Minimum + EPSILON) {
    return Vector(0, -1, 0);
  }
  return Vector(point.x, 0, point.z);
}

Intersections Cylinder::GetLocalIntersect(const Ray& r) const
{
  auto a = (r.direction.x * r.direction.x) + (r.direction.z * r.direction.z);

  Intersections xs{};

  // ray is parallel to the y axis
  if (a == 0) {
    IntersectCaps(r, xs);
    return xs;
  }

  auto b = (2 * r.origin.x * r.direction.x) + (2 * r.origin.z * r.direction.z);
  auto c = (r.origin.x * r.origin.x) + (r.origin.z * r.origin.z) - 1;

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

bool Cylinder::CheckCap(const Ray& r, float t) const
{
  auto x = r.origin.x + t * r.direction.x;
  auto z = r.origin.z + t * r.direction.z;

  return (x * x + z * z) <= 1;
}

void Cylinder::IntersectCaps(const Ray& r, Intersections& xs) const
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

void Cylinder::SetMinimum(float newMinimum)
{
  m_Minimum = newMinimum;
}

void Cylinder::SetMaximum(float newMaximum)
{
  m_Maximum = newMaximum;
}

void Cylinder::SetClosed(bool newClosed)
{
  m_Closed = newClosed;
}

/// ===========================================================================
/// @section Non-member functions
/// ===========================================================================

} // namespace RayTracer::Rendering::Primitives
