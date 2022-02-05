#pragma once
#include "RayTracerPCH.hpp"

#include "RayTracer/Rendering/Primitives/Shape.hpp"

namespace RayTracer {
namespace Rendering {
namespace Primitives {

using namespace Math;

class Cylinder : public Shape
{
public:
  /// @section Member functions
  ~Cylinder() override;
  Cylinder();
  Cylinder(const Cylinder&);
  Cylinder(Cylinder&&) noexcept;
  Cylinder& operator=(const Cylinder&);
  Cylinder& operator=(Cylinder&&) noexcept;

  /// @subsection Observers
  float GetMinimum() const;
  float GetMaximum() const;
  bool IsClosed() const;

  /// @subsection Modifiers
  void SetMinimum(float newMinimum);
  void SetMaximum(float newMaximum);
  void SetClosed(bool closed);

protected:
  Tuple GetLocalNormalAt(Tuple point,
                         const Intersection* i = nullptr) const override;
  Intersections VirtualIntersect(const Ray& r) const override;

private:
  bool CheckCap(const Ray& r, float t) const;
  void IntersectCaps(const Ray& r, Intersections& xs) const;

  float m_Minimum{ -INFINITY };
  float m_Maximum{ INFINITY };
  bool m_Closed{ false };
};

/// @section Non-member functions
inline bool operator==(const Shape& lhs, const Cylinder& rhs)
{
  return lhs == static_cast<const Shape&>(rhs);
}

inline bool operator==(const Shape* lhs, const Cylinder& rhs)
{
  return *lhs == static_cast<const Shape&>(rhs);
}

std::tuple<float, float> check_axis(float origin, float direction);

} // namespace Primitives
} // namespace Rendering
} // namespace RayTracer
