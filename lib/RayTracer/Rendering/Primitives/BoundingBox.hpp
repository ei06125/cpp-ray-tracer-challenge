#pragma once

#include "RayTracer/Rendering/Primitives/Shape.hpp"

namespace RayTracer {
namespace Rendering {
namespace Primitives {
using namespace Math;

// Forward declaration
class Group;

class BoundingBox : public Shape
{
public:
  /// @section Member functions
  BoundingBox(const std::shared_ptr<Shape>& shape);
  BoundingBox(const std::shared_ptr<Group>& group);

  /// @subsection Observers
  Tuple GetMinimum() const;
  Tuple GetMaximum() const;

protected:
  Tuple GetLocalNormalAt(Tuple point) const override;
  Intersections VirtualIntersect(const Ray& r) const override;

private:
  Tuple m_Minimum;
  Tuple m_Maximum;
};

/// @section Non-member functions

// ! implemented in Cube.cpp
std::tuple<float, float> check_axis(float origin, float direction);

} // namespace Primitives
} // namespace Rendering
} // namespace RayTracer
