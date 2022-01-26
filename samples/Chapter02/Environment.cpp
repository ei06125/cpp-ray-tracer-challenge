#include "Environment.hpp"

std::ostream& operator<<(std::ostream& os, const Environment& rhs)
{
  os << "{ "
     << "gravity:" << rhs.gravity << ","
     << "wind:" << rhs.wind << " }";
  return os;
}
