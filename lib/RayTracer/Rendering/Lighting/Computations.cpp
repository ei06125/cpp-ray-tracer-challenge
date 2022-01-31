#include "RayTracer/Rendering/Lighting/Computations.hpp"

#include "RayTracer/Math/Constants.hpp"
#include "RayTracer/Rendering/Lighting/Intersection.hpp"
#include "RayTracer/Rendering/Lighting/Ray.hpp"
#include "RayTracer/Rendering/Primitives/Shape.hpp"

namespace RayTracer {
namespace Rendering {
namespace Lighting {

using namespace Math::Constants;

Computations prepare_computations(const Intersection& i, const Ray& r)
{
  auto point = position(r, i.t);
  auto eyev = -r.direction;
  auto normalv = i.object->GetNormalAt(point);

  Computations comps{ i.t, i.object, point, eyev, normalv, point };

  if (dot(comps.normalv, comps.eyev) < 0) {
    comps.inside = true;
    comps.normalv = -comps.normalv;
  } else {
    comps.inside = false;
  }

  comps.over_point = comps.point + comps.normalv * EPSILON;

  return comps;
}

} // namespace Lighting
} // namespace Rendering
} // namespace RayTracer
