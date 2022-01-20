#pragma once

#include "Math/Matrix.hpp"
#include "Math/Tuple.hpp"

struct Ray
{
  Tuple origin;
  Tuple direction;
};

inline Tuple position(const Ray& ray, float time)
{
  return ray.origin + ray.direction * time;
}

inline Ray transform(const Ray& r, const Matrix<4, 4>& m)
{
  return { m * r.origin, m * r.direction };
}
