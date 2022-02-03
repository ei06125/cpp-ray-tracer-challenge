#pragma once

// Engine
#include "RayTracer.hpp"

using namespace RayTracer::Rendering::Primitives;
using namespace RayTracer::Rendering::Lighting;
using namespace RayTracer::Math;

class TestShape : public Shape
{
public:
  TestShape()
    : Shape()
    , saved_ray({ make_point(0, 0, 0), make_vector(0, 0, 1) })
  {}

  mutable Ray saved_ray;

protected:
  Tuple GetLocalNormalAt(Tuple point) const override
  {
    return make_vector(point.x, point.y, point.z);
  }

  Intersections VirtualIntersect(const Ray& r) const override
  {
    saved_ray = r;
    return {};
  }
};
