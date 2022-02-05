#pragma once
#include "RayTracerPCH.hpp"

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
  Tuple under_point;
  bool inside;
  Tuple reflectv;
  float n1{ 1.0 };
  float n2{ 1.0 };
};

// Forward Declarations
class Intersections;
struct Intersection;
struct Ray;

Computations prepare_computations(const Intersection& i,
                                  const Ray& r,
                                  const Intersections* xs = nullptr,
                                  std::vector<const Shape*>* objects = nullptr);

float schlick(const Computations& comps);

} // namespace Lighting
} // namespace Rendering
} // namespace RayTracer
