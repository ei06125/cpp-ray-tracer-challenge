#pragma once

#include "RayTracer/Math/Tuple.hpp"

namespace RayTracer {
namespace Rendering {

namespace Lighting {
struct PointLight;
} // namespace Lighting

namespace Materials {

using namespace Math;
using namespace Lighting;

struct Material
{
  Tuple color{ make_color(1, 1, 1) };
  float ambient{ 0.1 };
  float diffuse{ 0.9 };
  float specular{ 0.9 };
  float shininess{ 200.0 };
};

bool operator==(const Material& lhs, const Material& rhs);

Tuple lighting(const Material& material,
               const PointLight& light,
               const Tuple& point,
               const Tuple& eyev,
               const Tuple& normalv,
               bool in_shadow = false);

} // namespace Materials
} // namespace Rendering
} // namespace RayTracer
