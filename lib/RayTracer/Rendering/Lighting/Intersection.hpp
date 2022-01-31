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
  /// @section Member functions
  Intersection();
  explicit Intersection(float t_, const Shape* object_);
  Intersection(const Intersection&);
  Intersection(Intersection&&) noexcept;
  Intersection& operator=(const Intersection&);
  Intersection& operator=(Intersection&&) noexcept;
  ~Intersection();

  // TODO: move to Non-member functions
  bool operator<(const Intersection& rhs) const;
  bool operator==(const Intersection& rhs) const;

  /// @section Member functions
  float t;
  const Shape* object;
};

/// ===========================================================================
/// @section Intersections
/// ===========================================================================

class Intersections
{
public:
  /// @section Member functions
  Intersections();
  explicit Intersections(std::initializer_list<Intersection> points);
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
