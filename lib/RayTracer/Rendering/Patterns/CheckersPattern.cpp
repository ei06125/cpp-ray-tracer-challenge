#include "RayTracer/Rendering/Patterns/CheckersPattern.hpp"

#include "RayTracer/Rendering/Patterns/SolidColorPattern.hpp"

namespace RayTracer {
namespace Rendering {
namespace Patterns {

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

CheckersPattern::CheckersPattern(Color a, Color b)
  : Pattern()
  , m_PatternA(std::make_shared<SolidColorPattern>(a))
  , m_PatternB(std::make_shared<SolidColorPattern>(b))
{}

CheckersPattern::CheckersPattern(std::shared_ptr<Pattern> a,
                                 std::shared_ptr<Pattern> b)
  : Pattern()
  , m_PatternA(a)
  , m_PatternB(b)
{}

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------

Color CheckersPattern::At(Tuple point) const
{
  return std::fmod( //
           std::floor(point.x) + std::floor(point.y) + std::floor(point.z),
           2.0f) == 0
           ? m_PatternA->At(point)
           : m_PatternB->At(point);
}

} // namespace Patterns
} // namespace Rendering
} // namespace RayTracer
