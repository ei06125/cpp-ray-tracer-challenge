#pragma once

#include "RayTracer/Math/Matrix.hpp"
#include "RayTracer/Math/Tuple.hpp"
#include "RayTracer/Rendering/Lighting/Intersection.hpp"
#include "RayTracer/Rendering/Materials/Material.hpp"

namespace RayTracer {
namespace Rendering {
namespace Primitives {

using namespace Materials;
using namespace Lighting;
using namespace Math;

class Shape
{
public:
  /// @section Member functions
  virtual ~Shape();
  Shape(const Shape&);
  Shape(Shape&&) noexcept;
  Shape& operator=(const Shape&);
  Shape& operator=(Shape&&) noexcept;

  mat4 GetTransform() const;
  mat4& SetTransform();
  void SetTransform(mat4 t);

  Material GetMaterial() const;
  Material& SetMaterial();
  void SetMaterial(Material m);

  Tuple GetOrigin() const;
  Tuple& SetOrigin();
  void SetOrigin(Tuple t);

  virtual Tuple GetNormalAt(Tuple point) const;
  virtual Intersections Intersect(const Ray& r) const;

  bool operator==(const Shape& rhs) const;

protected:
  Shape();
  virtual Tuple GetLocalNormalAt(Tuple point) const = 0;
  virtual Intersections VirtualIntersect(const Ray& r) const = 0;

private:
  mat4 m_Transform;
  Material m_Material;
  Tuple m_Origin;
};

} // namespace Primitives
} // namespace Rendering
} // namespace RayTracer
