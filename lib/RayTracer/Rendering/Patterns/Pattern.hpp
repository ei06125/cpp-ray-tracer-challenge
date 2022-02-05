#pragma once
#include "RayTracerPCH.hpp"

#include "RayTracer/Math/Matrix.hpp"
#include "RayTracer/Math/Tuple.hpp"

namespace RayTracer {
namespace Rendering {

namespace Primitives {
class Shape;
} // namespace Primitives

namespace Patterns {

using namespace Rendering::Primitives;
using namespace Math;
using Color = Tuple;

class Pattern
{
public:
  /// @section Member functions
  virtual ~Pattern();
  Pattern(const Pattern&);
  Pattern(Pattern&&) noexcept;
  Pattern& operator=(const Pattern&);
  Pattern& operator=(Pattern&&) noexcept;

  /// @subsection Modifiers
  void SetTransform(mat4 newTransform);
  mat4& SetTransform();

  /// @subsection Observers
  mat4 GetTransform() const;

  virtual Color At(Tuple point) const = 0;
  virtual Color AtShape(const Shape* object, Tuple point) const;

  /// @subsection Friend functions
  friend bool operator==(const Pattern& lhs, const Pattern& rhs);

protected:
  Pattern();
  mat4 m_Transform;
};

/// @section Non-member functions
bool operator==(const Pattern& lhs, const Pattern& rhs);

} // namespace Patterns
} // namespace Rendering
} // namespace RayTracer
