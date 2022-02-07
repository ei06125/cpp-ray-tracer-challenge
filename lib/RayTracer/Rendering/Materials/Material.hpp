#pragma once
#include "RayTracerPCH.hpp"

#include "RayTracer/Math/Tuple.hpp"
#include "RayTracer/Rendering/Color.hpp"

namespace RayTracer {
namespace Rendering {

/// ===========================================================================
/// @section Forward Declarations
namespace Lighting {
struct PointLight;
} // namespace Lighting

namespace Patterns {
class Pattern;
} // namespace Patterns

namespace Primitives {
class Shape;
} // namespace Primitives
/// ===========================================================================

namespace Materials {

using namespace RayTracer::Math;
using namespace RayTracer::Rendering::Lighting;
using namespace RayTracer::Rendering::Primitives;
using namespace RayTracer::Rendering::Patterns;
using namespace RayTracer::Rendering::Colors;

struct Material
{
  Color color{ Colors::White };
  float ambient{ 0.1 };
  float diffuse{ 0.9 };
  float specular{ 0.9 };
  float shininess{ 200.0 };
  float reflective{ 0.0 };
  float transparency{ 0.0 };
  float refractiveIndex{ 1.0 };
  std::optional<std::shared_ptr<Pattern>> pattern;
};

/// @section Non-member functions

bool operator==(const Material& lhs, const Material& rhs);

/// @section API

Color lighting(const Material& material,
               const PointLight& light,
               const Tuple& point,
               const Tuple& eyev,
               const Tuple& normalv,
               bool in_shadow = false,
               const Shape* object = nullptr);

} // namespace Materials
} // namespace Rendering
} // namespace RayTracer
