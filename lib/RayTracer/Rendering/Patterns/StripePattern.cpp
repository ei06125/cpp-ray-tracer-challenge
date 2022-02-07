#include "RayTracer/Rendering/Patterns/StripePattern.hpp"

namespace RayTracer {
namespace Rendering {
namespace Patterns {

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

StripePattern::StripePattern(Color a, Color b)
  : Pattern()
  , m_ColorA(a)
  , m_ColorB(b)
{}

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------

Color StripePattern::A() const
{
  return m_ColorA;
}

Color StripePattern::B() const
{
  return m_ColorB;
}

Color StripePattern::At(Tuple point) const
{
  return std::fmod(std::floor(point.x), 2.0f) == 0 ? m_ColorA : m_ColorB;
}

} // namespace Patterns
} // namespace Rendering
} // namespace RayTracer
