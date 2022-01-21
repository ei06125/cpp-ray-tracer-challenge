#pragma once

#include "Math/Matrix.hpp"
#include "Math/Tuple.hpp"
#include "Rendering/RayTracing/Material.hpp"

struct Sphere
{
  static std::size_t SphereID;

  Sphere();

  mat4 transform;
  Material material;
  Tuple origin;
  float radius;
  std::size_t id;
};

bool operator==(const Sphere& lhs, const Sphere& rhs);

void set_transform(Sphere& s, mat4 t);

Tuple normal_at(const Sphere& s, const Tuple& world_point);