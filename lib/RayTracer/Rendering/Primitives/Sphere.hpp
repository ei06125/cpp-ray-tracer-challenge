#pragma once

#include "RayTracer/Rendering/Primitives/Shape.hpp"

namespace RayTracer::Rendering::Primitives {
using namespace Math;

class Sphere : public Shape
{
public:
  ~Sphere() override;
  Sphere();

  float GetRadius() const;
  void SetRadius(float r);

  bool operator==(const Sphere& rhs) const;

protected:
  Tuple GetLocalNormalAt(Tuple point) const override;
  Intersections VirtualIntersect(const Ray& r) const override;

private:
  float m_Radius;
};

} // namespace RayTracer::Rendering::Primitives