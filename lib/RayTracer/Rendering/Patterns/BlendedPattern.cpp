#include "RayTracer/Rendering/Patterns/BlendedPattern.hpp"

namespace RayTracer {
namespace Rendering {
namespace Patterns {

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

BlendedPattern::BlendedPattern(std::shared_ptr<Pattern> a,
                               std::shared_ptr<Pattern> b)
  : Pattern()
  , m_PatternA(a)
  , m_PatternB(b)
{}

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------

Color BlendedPattern::At(Tuple point) const
{
  auto localPointA = inverse(m_PatternA->GetTransform()) * point;
  auto colorA = m_PatternA->At(localPointA);
  auto localPointB = inverse(m_PatternB->GetTransform()) * point;
  auto colorB = m_PatternB->At(localPointB);
  return colorA + colorB;
}

} // namespace Textures
} // namespace Rendering
} // namespace RayTracer
