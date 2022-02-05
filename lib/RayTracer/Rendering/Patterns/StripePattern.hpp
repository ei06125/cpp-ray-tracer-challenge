#pragma once
#include "RayTracerPCH.hpp"

#include "RayTracer/Math/Tuple.hpp"
#include "RayTracer/Rendering/Patterns/Pattern.hpp"

namespace RayTracer {
namespace Rendering {
namespace Patterns {

class StripePattern : public Pattern
{
public:
  /// @section Member functions
  StripePattern(Color a, Color b);

  /// @subsection Observers
  Color A() const;
  Color B() const;
  Color At(Tuple point) const override;

  private:
  Color m_ColorA;
  Color m_ColorB;
};

} // namespace Textures
} // namespace Rendering
} // namespace RayTracer
