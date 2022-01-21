#pragma once

// C++ Standard Library
#include <iosfwd>

// Project Library
#include "Math/Tuple.hpp"

struct PointLight
{
  Tuple position;
  Tuple intensity;
};

std::ostream& operator<<(std::ostream& os, const PointLight& aLight);
