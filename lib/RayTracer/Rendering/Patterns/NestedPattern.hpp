#pragma once

#include "RayTracer/Math/Tuple.hpp"
#include "RayTracer/Rendering/Patterns/Pattern.hpp"

namespace RayTracer {
namespace Rendering {
namespace Patterns {

class NestedPattern : public Pattern
{
public:
  /// @section Member functions
  NestedPattern(std::shared_ptr<Pattern> inner, std::shared_ptr<Pattern> outer);

  /// @subsection Observers
  Color At(Tuple point) const override;

private:
  std::shared_ptr<Pattern> innerPattern;
  std::shared_ptr<Pattern> outerPattern;
};

} // namespace Textures
} // namespace Rendering
} // namespace RayTracer
