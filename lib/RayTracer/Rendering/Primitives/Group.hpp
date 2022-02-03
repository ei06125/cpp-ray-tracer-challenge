#pragma once

#include "RayTracer/Rendering/Primitives/Shape.hpp"

#include <unordered_set>

namespace RayTracer {
namespace Rendering {
namespace Primitives {

using namespace Math;

class Group : public Shape, public std::enable_shared_from_this<Group>
{
public:
  /// @section Member functions
  /// @subsection Observers
  bool IsEmpty() const;
  bool Contains(const std::shared_ptr<Shape>& shape) const;

  /// @subsubsection Virtual member functions
  Tuple GetNormalAt(Tuple point) const override;

  /// @subsection Modifiers
  void AddChild(std::shared_ptr<Shape> newChild);

protected:
  Tuple GetLocalNormalAt(Tuple point) const override;
  Intersections VirtualIntersect(const Ray& r) const override;

private:
  std::unordered_set<std::shared_ptr<Shape>> m_Children;
};

/// @section Non-member functions

} // namespace Primitives
} // namespace Rendering
} // namespace RayTracer
