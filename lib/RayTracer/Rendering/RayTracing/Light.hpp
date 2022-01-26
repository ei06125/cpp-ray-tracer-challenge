#pragma once

// Project Library
#include "RayTracer/Math/Tuple.hpp"

struct PointLight
{
  Tuple position;
  Tuple intensity;
};

std::ostream& operator<<(std::ostream& os, const PointLight& aLight);

bool operator==(const PointLight& lhs, const PointLight& rhs);
