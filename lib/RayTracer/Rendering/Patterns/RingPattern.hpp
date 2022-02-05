#pragma once
#include "RayTracerPCH.hpp"

#include "RayTracer/Math/Tuple.hpp"
#include "RayTracer/Rendering/Patterns/Pattern.hpp"

namespace RayTracer {
namespace Rendering {

namespace Patterns {

class RingPattern : public Pattern
{
public:
  /// @section Member functions
  RingPattern(Color a, Color b);

  /// @subsection Observers
  Color At(Tuple point) const override;

private:
  Color m_ColorA;
  Color m_ColorB;
};

} // namespace Textures
} // namespace Rendering
} // namespace RayTracer
