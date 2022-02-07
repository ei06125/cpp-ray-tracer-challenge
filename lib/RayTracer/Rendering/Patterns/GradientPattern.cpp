#include "RayTracer/Rendering/Patterns/GradientPattern.hpp"

namespace RayTracer {
namespace Rendering {
namespace Patterns {

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

GradientPattern::GradientPattern(Color a, Color b)
  : Pattern()
  , m_ColorA(a)
  , m_ColorB(b)
{}

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------
Color GradientPattern::At(Tuple point) const
{
  auto distance = m_ColorB - m_ColorA;
  auto fraction = point.x - std::floor(point.x);
  return m_ColorA + distance * fraction;
}

} // namespace Patterns
} // namespace Rendering
} // namespace RayTracer
