#pragma once

#include "RayTracer/Math/Matrix.hpp"
#include "RayTracer/Math/Tuple.hpp"

struct Ray
{
  Tuple origin;
  Tuple direction;
};

Tuple position(const Ray& ray, float time);
Ray transform(const Ray& r, const mat4& m);
