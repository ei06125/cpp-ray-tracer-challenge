#include "RayTracer/Rendering/Patterns/Pattern.hpp"

#include "RayTracer/Rendering/Primitives/Shape.hpp"

namespace RayTracer {
namespace Rendering {
namespace Patterns {

/// ===========================================================================
/// @section Member functions
/// ===========================================================================

Pattern::~Pattern() = default;
Pattern::Pattern()
  : m_Transform(mat4::Identity())
{}
Pattern::Pattern(const Pattern& other) = default;
Pattern::Pattern(Pattern&& other) noexcept = default;
Pattern& Pattern::operator=(const Pattern& other) = default;
Pattern& Pattern::operator=(Pattern&& other) noexcept = default;

/// ---------------------------------------------------------------------------
/// @subsection Modifiers
/// ---------------------------------------------------------------------------

void Pattern::SetTransform(mat4 newTransform)
{
  m_Transform = newTransform;
}

mat4& Pattern::SetTransform()
{
  return m_Transform;
}

/// ---------------------------------------------------------------------------
/// @subsection Observers
/// ---------------------------------------------------------------------------

mat4 Pattern::GetTransform() const
{
  return m_Transform;
}

Color Pattern::AtShape(const Shape* object, Tuple point) const
{
  auto object_point = inverse(object->GetTransform()) * point;
  auto pattern_point = inverse(GetTransform()) * object_point;
  return At(pattern_point);
}

/// ===========================================================================
/// @section Non-member functions
/// ===========================================================================

bool operator==(const Pattern& lhs, const Pattern& rhs)
{
  return lhs.m_Transform == rhs.m_Transform;
}

} // namespace Patterns
} // namespace Rendering
} // namespace RayTracer
