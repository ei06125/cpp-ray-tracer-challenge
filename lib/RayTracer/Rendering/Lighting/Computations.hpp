#pragma once

#include "RayTracer/Math/Tuple.hpp"

namespace RayTracer {
namespace Rendering {

// Forward Declaration
namespace Primitives {
class Shape;
} // namespace Primitives

namespace Lighting {

using namespace Math;
using namespace Primitives;

struct Computations
{
  float t;
  const Shape* object;
  Tuple point;
  Tuple eyev;
  Tuple normalv;
  Tuple over_point;
  bool inside;
};

// Forward Declarations
struct Intersection;
struct Ray;

Computations prepare_computations(const Intersection& i, const Ray& r);

} // namespace Lighting
} // namespace Rendering
} // namespace RayTracer
