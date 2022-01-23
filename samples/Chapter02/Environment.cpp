#include "Environment.hpp"

#include <iostream>

inline std::ostream &operator<<(std::ostream &os, const Environment &rhs) {
  os << "{ "
     << "gravity:" << rhs.gravity << ","
     << "wind:" << rhs.wind << " }";
  return os;
}
