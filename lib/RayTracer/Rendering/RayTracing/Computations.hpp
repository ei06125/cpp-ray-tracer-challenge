#pragma once

#include "RayTracer/Math/Tuple.hpp"

struct Intersection;
struct Ray;
class Shape;

struct Computations
{
  float t;
  const Shape* object;
  Tuple point;
  Tuple eyev;
  Tuple normalv;
  Tuple over_point;
  bool inside;
};

Computations prepare_computations(const Intersection& i, const Ray& r);
