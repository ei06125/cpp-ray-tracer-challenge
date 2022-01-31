#pragma once

#include "RayTracer/Math/Tuple.hpp"
#include "RayTracer/Rendering/Patterns/Pattern.hpp"

namespace RayTracer {
namespace Rendering {

namespace Patterns {

class GradientPattern : public Pattern
{
public:
  /// @section Member functions
  GradientPattern(Color a_, Color b_);

  /// @subsection Observers
  Color At(Tuple point) const override;

private:
  Color m_ColorA;
  Color m_ColorB;
};

} // namespace Textures
} // namespace Rendering
} // namespace RayTracer
