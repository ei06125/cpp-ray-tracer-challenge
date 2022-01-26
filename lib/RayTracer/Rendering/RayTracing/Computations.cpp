#include "RayTracer/Rendering/RayTracing/Computations.hpp"

#include "RayTracer/Rendering/Primitives/Shape.hpp"
#include "RayTracer/Rendering/RayTracing/Intersection.hpp"
#include "RayTracer/Rendering/RayTracing/Ray.hpp"

Computations prepare_computations(const Intersection& i, const Ray& r)
{
  auto point = ::position(r, i.t);
  auto eyev = -r.direction;
  auto normalv = i.object->GetNormalAt(point);

  Computations comps{ i.t, i.object, point, eyev, normalv, point };

  if (::dot(comps.normalv, comps.eyev) < 0) {
    comps.inside = true;
    comps.normalv = -comps.normalv;
  } else {
    comps.inside = false;
  }

  comps.over_point = comps.point + comps.normalv * EPSILON;

  return comps;
}
