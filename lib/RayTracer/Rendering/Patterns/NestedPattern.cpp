#include "NestedPattern.hpp"

namespace RayTracer {
namespace Rendering {
namespace Patterns {

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

NestedPattern::NestedPattern(std::shared_ptr<Pattern> inner,
                             std::shared_ptr<Pattern> outer)
  : Pattern()
  , innerPattern(inner)
  , outerPattern(outer)
{}

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------
Color NestedPattern::At(Tuple point) const
{
  auto localPointA = inverse(innerPattern->GetTransform()) * point;
  auto colorA = innerPattern->At(localPointA);
  auto localPointB = inverse(outerPattern->GetTransform()) * point;
  auto colorB = outerPattern->At(localPointB);
  return colorA + colorB;
}

} // namespace Textures
} // namespace Rendering
} // namespace RayTracer
