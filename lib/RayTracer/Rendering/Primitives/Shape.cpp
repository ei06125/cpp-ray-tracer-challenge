#include "RayTracer/Rendering/Primitives/Shape.hpp"

namespace RayTracer {
namespace Rendering {
namespace Primitives {

using namespace Math;

Shape::~Shape() = default;

Shape::Shape()
  : m_Transform(mat4::Identity())
  , m_Material(Material())
  , m_Origin(make_point(0, 0, 0))
{}

mat4 Shape::GetTransform() const
{
  return m_Transform;
}

mat4& Shape::SetTransform()
{
  return m_Transform;
}

void Shape::SetTransform(mat4 newTransform)
{
  m_Transform = newTransform;
}

Material Shape::GetMaterial() const
{
  return m_Material;
}

Material& Shape::SetMaterial()
{
  return m_Material;
}

void Shape::SetMaterial(Material newMaterial)
{
  m_Material = newMaterial;
}

Tuple Shape::GetOrigin() const
{
  return m_Origin;
}

Tuple& Shape::SetOrigin()
{
  return m_Origin;
}

void Shape::SetOrigin(Tuple newOrigin)
{
  m_Origin = newOrigin;
}

Tuple Shape::GetNormalAt(Tuple worldPoint) const
{
  auto localPoint = inverse(m_Transform) * worldPoint;
  auto localNormal = this->GetLocalNormalAt(localPoint);
  auto worldNormal = transpose(inverse(m_Transform)) * localNormal;
  worldNormal.w = 0;

  return normalize(worldNormal);
}

Intersections Shape::Intersect(const Ray& ray) const
{
  auto localRay = transform(ray, inverse(m_Transform));
  return this->VirtualIntersect(localRay);
}

bool Shape::operator==(const Shape& rhs) const
{
  return m_Material == rhs.m_Material && m_Transform == rhs.m_Transform &&
         m_Origin == rhs.m_Origin;
}

} // namespace Primitives
} // namespace Rendering
} // namespace RayTracer
