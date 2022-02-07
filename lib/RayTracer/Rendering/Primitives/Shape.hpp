#pragma once
#include "RayTracerPCH.hpp"

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

/**
 * @brief Base class for all shapes
 * @implements Composite design pattern
 */
class Shape
{
public:
  /// @section Member functions
  /// @subsection Special member functions
  virtual ~Shape();

  /// @subsection Observers
  mat4 GetTransform() const;
  Material GetMaterial() const;
  Tuple GetOrigin() const;
  std::weak_ptr<Shape> GetParent() const;
  Tuple WorldToObject(Tuple point) const;
  Tuple NormalToWorld(Tuple normal) const;

  /// @subsubsection Virtual member functions
  virtual Tuple GetNormalAt(Tuple point, const Intersection* i = nullptr) const;
  virtual Intersections Intersect(const Ray& r) const;

  /// @subsection Modifiers
  mat4& SetTransform();
  void SetTransform(mat4 t);
  Material& SetMaterial();
  void SetMaterial(Material m);
  Tuple& SetOrigin();
  void SetOrigin(Tuple t);
  void SetParent(std::shared_ptr<Shape> parent);

  /// @section Friend functions
  bool operator==(const Shape& rhs) const;

protected:
  Shape();
  virtual Tuple GetLocalNormalAt(Tuple point,
                                 const Intersection* i = nullptr) const = 0;
  virtual Intersections GetLocalIntersect(const Ray& r) const = 0;

private:
  mat4 m_Transform;
  Material m_Material;
  Tuple m_Origin;
  std::weak_ptr<Shape> m_Parent;
};

/// @section Non-member functions
Tuple world_to_object(const std::shared_ptr<Shape>& shape, Tuple worldPoint);

} // namespace Primitives
} // namespace Rendering
} // namespace RayTracer
