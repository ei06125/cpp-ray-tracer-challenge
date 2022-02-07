#pragma once
#include "RayTracerPCH.hpp"

// Project Library
#include "RayTracer/Math/Tuple.hpp"
#include "RayTracer/Rendering/Color.hpp"

namespace RayTracer {
namespace Rendering {
namespace Lighting {

using namespace RayTracer::Math;
using namespace RayTracer::Rendering::Colors;

struct PointLight
{
  Tuple position;
  Color intensity;
};

std::ostream& operator<<(std::ostream& os, const PointLight& aLight);

bool operator==(const PointLight& lhs, const PointLight& rhs);

} // namespace Lighting
} // namespace Rendering
} // namespace RayTracer
