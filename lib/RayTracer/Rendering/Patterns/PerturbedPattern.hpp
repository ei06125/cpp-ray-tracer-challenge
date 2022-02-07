#pragma once
#include "RayTracerPCH.hpp"

#include "RayTracer/Math/Tuple.hpp"
#include "RayTracer/Rendering/Patterns/Pattern.hpp"

namespace RayTracer {
namespace Rendering {
namespace Patterns {

class PerturbedPattern : public Pattern
{
public:
  /// @section Member functions
  PerturbedPattern(std::shared_ptr<Pattern> sub);

  /// @subsection Observers
  Color At(Tuple point) const override;

private:
  std::shared_ptr<Pattern> m_SubPattern;
};

} // namespace Patterns
} // namespace Rendering
} // namespace RayTracer
