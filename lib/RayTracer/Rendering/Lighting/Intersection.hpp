#pragma once

#include "RayTracer/Rendering/Lighting/Ray.hpp"

#include <initializer_list>
#include <vector>

namespace RayTracer {
namespace Rendering {

// Forward Declaration
namespace Primitives {
class Shape;
} // namespace Primitives

namespace Lighting {

using namespace Math;
using namespace Primitives;

/// ===========================================================================
/// @section Intersection
/// ===========================================================================

struct Intersection
{
  float t;
  const Shape* object;
};

inline bool operator<(const Intersection& lhs, const Intersection& rhs)
{
  return lhs.t < rhs.t;
}

inline bool operator==(const Intersection& lhs, const Intersection& rhs)
{
  return lhs.t == rhs.t && lhs.object == rhs.object;
}

/// ===========================================================================
/// @section Intersections
/// ===========================================================================

class Intersections
{
public:
  /// @section Member functions
  Intersections();
  explicit Intersections(std::initializer_list<Intersection> points);
  explicit Intersections(std::vector<Intersection>&& points);
  Intersections(float t, const Shape* shapePtr);
  Intersections(const Intersections&);
  Intersections(Intersections&&);
  ~Intersections();
  Intersections& operator=(const Intersections&);
  Intersections& operator=(Intersections&&);

  /// @subsection Element access
  Intersection& operator[](std::size_t index);
  Intersection operator[](std::size_t index) const;

  /// @subsection Capacity
  std::size_t Count() const;
  void Reserve(std::size_t newCapacity);

  /// @subsection Observers
  const std::vector<Intersection>& GetIntersectionPoints() const;

  /// @subsection Modifiers
  std::vector<Intersection>& Data();
  template<typename... Args>
  void EmplaceBack(Args&&... args)
  {
    intersectionPoints.emplace_back(std::forward<Args>(args)...);
  }
  void Sort();
  const Intersection* Hit() const;

private:
  std::vector<Intersection> intersectionPoints;
};

} // namespace Lighting
} // namespace Rendering
} // namespace RayTracer
