#include "RadialGradientPattern.hpp"

namespace RayTracer {
namespace Rendering {
namespace Patterns {

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

RadialGradientPattern::RadialGradientPattern(Color a, Color b)
  : Pattern()
  , m_ColorA(a)
  , m_ColorB(b)
{}

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------
Color RadialGradientPattern::At(Tuple point) const
{
  auto distance = m_ColorB - m_ColorA;

  auto magnitude = std::sqrt((point.x * point.x) + (point.z * point.z));
  auto fraction = magnitude - std::floor(magnitude);

  auto gradientA = m_ColorA + distance * fraction;
  auto gradientB = m_ColorB - distance * fraction;

  return std::fmod(std::floor(magnitude), 2.0f) == 0 ? gradientA : gradientB;
}

} // namespace Patterns
} // namespace Rendering
} // namespace RayTracer
