#pragma once
#include "RayTracerPCH.hpp"

#include "RayTracer/Math/Tuple.hpp"
#include "RayTracer/Rendering/Patterns/Pattern.hpp"

namespace RayTracer {
namespace Rendering {

namespace Patterns {

class CheckersPattern : public Pattern
{
public:
  /// @section Member functions
  CheckersPattern(Color a, Color b);
  CheckersPattern(std::shared_ptr<Pattern> a, std::shared_ptr<Pattern> b);

  /// @subsection Observers
  Color At(Tuple point) const override;

private:
  std::shared_ptr<Pattern> m_PatternA;
  std::shared_ptr<Pattern> m_PatternB;
};

} // namespace Patterns
} // namespace Rendering
} // namespace RayTracer
