#pragma once
#include "RayTracerPCH.hpp"

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
    , saved_ray({ Point(0, 0, 0), Vector(0, 0, 1) })
  {}

  mutable Ray saved_ray;

protected:
  Tuple GetLocalNormalAt(Tuple point, const Intersection*) const override
  {
    return Vector(point.x, point.y, point.z);
  }

  Intersections GetLocalIntersect(const Ray& r) const override
  {
    saved_ray = r;
    return {};
  }
};
