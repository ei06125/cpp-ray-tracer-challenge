#include "SolidColorPattern.hpp"

namespace RayTracer {
namespace Rendering {
namespace Patterns {

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

SolidColorPattern::SolidColorPattern(Color aColor)
  : Pattern()
  , m_Color(aColor)
{}

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------

Color SolidColorPattern::At(Tuple point) const
{
  return m_Color;
}

} // namespace Textures
} // namespace Rendering
} // namespace RayTracer
