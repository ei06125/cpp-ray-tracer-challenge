#include "RayTracer/Rendering/Patterns/RingPattern.hpp"

namespace RayTracer {
namespace Rendering {
namespace Patterns {

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

RingPattern::RingPattern(Color a, Color b)
  : Pattern()
  , m_ColorA(a)
  , m_ColorB(b)
{}

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------

Color RingPattern::At(Tuple point) const
{
  return std::fmod( //
           std::floor(std::sqrt(std::pow(point.x, 2) + std::pow(point.z, 2))),
           2.0f) == 0
           ? m_ColorA
           : m_ColorB;
}

} // namespace Patterns
} // namespace Rendering
} // namespace RayTracer
