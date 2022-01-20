#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <iosfwd>

#include "Math/Tuple.hpp"

struct Environment {
  using Vector = Tuple;
  using Point = Tuple;
  Vector gravity;
  Vector wind;
};

std::ostream &operator<<(std::ostream &os, const Environment &rhs);

#endif // ENVIRONMENT_HPP
