#pragma once
#include "RayTracerPCH.hpp"

#include "RayTracer/Math/Tuple.hpp"
#include "RayTracer/Rendering/Patterns/Pattern.hpp"

namespace RayTracer {
namespace Rendering {
namespace Patterns {

class SolidColorPattern : public Pattern
{
public:
  /// @section Member functions
  SolidColorPattern(Color aColor);

  /// @subsection Observers
  Color At(Tuple point) const override;

private:
  Color m_Color;
};

} // namespace Textures
} // namespace Rendering
} // namespace RayTracer
