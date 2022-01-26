#include "Projectile.hpp"

std::ostream& operator<<(std::ostream& os, const Projectile& rhs)
{
  os << "{ "
     << "Position:" << rhs.position << ", "
     << "Velocity:" << rhs.velocity << " }";
  return os;
}
