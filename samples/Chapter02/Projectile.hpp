#pragma once

#include "RayTracer.hpp"

struct Projectile
{
  using Vector = Tuple;
  using Point = Tuple;
  Point position;
  Vector velocity;
};

std::ostream& operator<<(std::ostream& os, const Projectile& rhs);
