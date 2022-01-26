#pragma once

#include "RayTracer/Rendering/Lighting/Ray.hpp"

namespace RayTracer {
namespace Rendering {

// Forward Declaration
namespace Primitives {
class Shape;
} // namespace Primitives

namespace Lighting {

using namespace Math;
using namespace Primitives;

struct Intersection
{
  Intersection(float t_, const Shape* object_);

  float t;
  const Shape* object;

  bool operator<(const Intersection& rhs) const;
  bool operator==(const Intersection& rhs) const;
};

class Intersections
{
public:
  Intersections();
  Intersections(std::initializer_list<Intersection> points);
  std::size_t Count() const;
  Intersection& operator[](std::size_t index);
  Intersection operator[](std::size_t index) const;

  template<typename... Args>
  void Add(Args&&... args)
  {
    intersectionPoints.emplace_back(args...);
  }

  std::vector<Intersection>& GetIntersectionPoints();

  Intersection* Hit();

private:
  std::vector<Intersection> intersectionPoints;
};

} // namespace Lighting
} // namespace Rendering
} // namespace RayTracer
