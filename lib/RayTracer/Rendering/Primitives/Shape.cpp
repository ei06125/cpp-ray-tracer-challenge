#include "RayTracer/Rendering/Primitives/Shape.hpp"

namespace RayTracer {
namespace Rendering {
namespace Primitives {

using namespace Math;

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

/// ---------------------------------------------------------------------------
/// @subsection Special member functions
/// ---------------------------------------------------------------------------

Shape::~Shape() = default;
Shape::Shape()
  : m_Transform(mat4::Identity())
  , m_Material(Material())
  , m_Origin(make_point(0, 0, 0))
  , m_Parent()
{}

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------

mat4 Shape::GetTransform() const
{
  return m_Transform;
}

Material Shape::GetMaterial() const
{
  return m_Material;
}

Tuple Shape::GetOrigin() const
{
  return m_Origin;
}

std::weak_ptr<Shape> Shape::GetParent() const
{
  return m_Parent;
}

Tuple Shape::WorldToObject(Tuple point) const
{
  if (!m_Parent.expired()) {
    point = m_Parent.lock()->WorldToObject(point);
  }
  return inverse(m_Transform) * point;
}

Tuple Shape::NormalToWorld(Tuple normal) const
{
  normal = transpose(inverse(m_Transform)) * normal;
  normal.w = 0;
  normal = normalize(normal);

  if (!m_Parent.expired()) {
    normal = m_Parent.lock()->NormalToWorld(normal);
  }
  return normal;
}

///
/// @subsubsection Virtual member functions
///

Tuple Shape::GetNormalAt(Tuple worldPoint, const Intersection* i) const
{
  auto localPoint = WorldToObject(worldPoint);
  auto localNormal = GetLocalNormalAt(localPoint, i);
  return NormalToWorld(localNormal);
}

Intersections Shape::Intersect(const Ray& ray) const
{
  auto localRay = transform(ray, inverse(m_Transform));
  return VirtualIntersect(localRay);
}

/// ---------------------------------------------------------------------------
/// @subsection Modifiers
/// ---------------------------------------------------------------------------

mat4& Shape::SetTransform()
{
  return m_Transform;
}

void Shape::SetTransform(mat4 newTransform)
{
  m_Transform = newTransform;
}

Material& Shape::SetMaterial()
{
  return m_Material;
}

void Shape::SetMaterial(Material newMaterial)
{
  m_Material = newMaterial;
}

Tuple& Shape::SetOrigin()
{
  return m_Origin;
}

void Shape::SetOrigin(Tuple newOrigin)
{
  m_Origin = newOrigin;
}

void Shape::SetParent(std::shared_ptr<Shape> parent)
{
  m_Parent = parent;
}

/// ===========================================================================
/// @section Non-member functions
/// ===========================================================================

bool Shape::operator==(const Shape& rhs) const
{
  return m_Material == rhs.m_Material && m_Transform == rhs.m_Transform &&
         m_Origin == rhs.m_Origin;
}

} // namespace Primitives
} // namespace Rendering
} // namespace RayTracer
