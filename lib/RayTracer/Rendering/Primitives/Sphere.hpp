#pragma once
#include "RayTracerPCH.hpp"

#include "RayTracer/Rendering/Primitives/Shape.hpp"

namespace RayTracer::Rendering::Primitives {
using namespace Math;

class Sphere : public Shape
{
public:
  /// @section Member functions
  /// @subsection Observers
  float GetRadius() const;

  /// @subsection Modifiers
  void SetRadius(float r);

  /// @section Friend functions
  bool operator==(const Sphere& rhs) const;
  friend bool operator==(const Sphere& lhs, const Sphere& rhs);

protected:
  Tuple GetLocalNormalAt(Tuple point,
                         const Intersection* i = nullptr) const override;
  Intersections GetLocalIntersect(const Ray& r) const override;

private:
  float m_Radius{ 1.0f };
};

/// @section Non-member functions
bool operator==(const Sphere& lhs, const Sphere& rhs);

/// @subsection Creation methods
Sphere GlassSphere();

} // namespace RayTracer::Rendering::Primitives
