#pragma once

// Project Library
#include "RayTracer/Math/Tuple.hpp"

namespace RayTracer {
namespace Rendering {
namespace Lighting {

using namespace Math;

struct PointLight
{
  Tuple position;
  Tuple intensity;
};

std::ostream& operator<<(std::ostream& os, const PointLight& aLight);

bool operator==(const PointLight& lhs, const PointLight& rhs);

} // namespace Lighting
} // namespace Rendering
} // namespace RayTracer
