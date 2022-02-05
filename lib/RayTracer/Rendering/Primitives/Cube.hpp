#pragma once
#include "RayTracerPCH.hpp"

#include "RayTracer/Rendering/Primitives/Shape.hpp"

namespace RayTracer {
namespace Rendering {
namespace Primitives {

using namespace Math;

class Cube : public Shape
{
public:
  /// @section Member functions
  ~Cube() override;
  Cube();
  Cube(const Cube&);
  Cube(Cube&&) noexcept;
  Cube& operator=(const Cube&);
  Cube& operator=(Cube&&) noexcept;

protected:
  Tuple GetLocalNormalAt(Tuple point,
                         const Intersection* i = nullptr) const override;
  Intersections VirtualIntersect(const Ray& r) const override;
};

/// @section Non-member functions
inline bool operator==(const Shape& lhs, const Cube& rhs)
{
  return lhs == static_cast<const Shape&>(rhs);
}

inline bool operator==(const Shape* lhs, const Cube& rhs)
{
  return *lhs == static_cast<const Shape&>(rhs);
}

std::tuple<float, float> check_axis(float origin, float direction);

} // namespace Primitives
} // namespace Rendering
} // namespace RayTracer
