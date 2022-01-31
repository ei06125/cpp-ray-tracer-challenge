#include "RayTracer/Rendering/Patterns/PerturbedPattern.hpp"

#include "RayTracer/Math/PerlinNoise.hpp"

namespace RayTracer {
namespace Rendering {
namespace Patterns {

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

PerturbedPattern::PerturbedPattern(std::shared_ptr<Pattern> sub)
  : Pattern()
  , m_SubPattern(sub)
{}

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------
Color PerturbedPattern::At(Tuple point) const
{
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<unsigned int> distrib(0);

  const siv::PerlinNoise::seed_type seed{ distrib(gen) };
  const siv::PerlinNoise perlin{ seed };

  const auto localPoint = inverse(m_SubPattern->GetTransform()) * point;

  auto perturbedPoint = make_point(perlin.noise1D_01(localPoint.x),
                                   perlin.noise1D_01(localPoint.y),
                                   perlin.noise1D_01(localPoint.z));

  return m_SubPattern->At(perturbedPoint);
}

} // namespace Textures
} // namespace Rendering
} // namespace RayTracer
