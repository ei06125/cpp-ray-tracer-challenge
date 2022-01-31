#pragma once

#include "RayTracer/Rendering/Primitives/Shape.hpp"

namespace RayTracer::Rendering::Primitives {
using namespace Math;

class Sphere : public Shape
{
public:
  /// @section Member functions
  ~Sphere() override;
  Sphere();
  Sphere(const Sphere&);
  Sphere(Sphere&&) noexcept;
  Sphere& operator=(const Sphere&);
  Sphere& operator=(Sphere&&) noexcept;

  /// @subsection Observers
  float GetRadius() const;

  /// @subsection Modifiers
  void SetRadius(float r);

  /// @section Friend functions
  friend bool operator==(const Sphere& lhs, const Sphere& rhs);

protected:
  Tuple GetLocalNormalAt(Tuple point) const override;
  Intersections VirtualIntersect(const Ray& r) const override;

private:
  float m_Radius;
};

/// @section Non-member functions
bool operator==(const Sphere& lhs, const Sphere& rhs);

} // namespace RayTracer::Rendering::Primitives
