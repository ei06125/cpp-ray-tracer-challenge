#pragma once

#include "Math/Matrix.hpp"
#include "Math/Tuple.hpp"

struct Sphere
{
  static std::size_t SphereID;

  Sphere();

  mat4 transform;
  Tuple origin;
  float radius;
  std::size_t id;
};

bool operator==(const Sphere& lhs, const Sphere& rhs);

void set_transform(Sphere& s, mat4 t);