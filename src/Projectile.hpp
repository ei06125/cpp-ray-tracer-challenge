#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <iosfwd>

#include "Tuple.hpp"

struct Projectile {
  using Vector = Tuple;
  using Point = Tuple;
  Point position;
  Vector velocity;
};

std::ostream &operator<<(std::ostream &os, const Projectile &rhs);

#endif // PROJECTILE_HPP
