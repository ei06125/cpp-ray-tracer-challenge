#include "RayTracer/Rendering/Lighting/Computations.hpp"

#include "RayTracer/Math/Constants.hpp"
#include "RayTracer/Rendering/Lighting/Intersection.hpp"
#include "RayTracer/Rendering/Lighting/Ray.hpp"
#include "RayTracer/Rendering/Primitives/Shape.hpp"

#include <algorithm>

#include "RayTracer/Utils/Print.hpp"

namespace RayTracer {
namespace Rendering {
namespace Lighting {

using namespace Math::Constants;

Computations prepare_computations(const Intersection& i,
                                  const Ray& r,
                                  const Intersections* xs,
                                  std::vector<const Shape*>* objects)
{
  auto point = position(r, i.t);
  auto eyev = -r.direction;
  auto normalv = i.object->GetNormalAt(point, &i);

  Computations comps{ i.t,   i.object, point, eyev, normalv,
                      point, point,    false, point };

  if (dot(comps.normalv, comps.eyev) < 0) {
    comps.inside = true;
    comps.normalv = -comps.normalv;
  }

  comps.over_point = comps.point + comps.normalv * EPSILON;
  comps.under_point = comps.point - comps.normalv * EPSILON;
  comps.reflectv = reflect(r.direction, comps.normalv);

  if (!xs || !objects) {
    return comps;
  }

  if (auto hit = xs->Hit(); hit) {
    /// -----------------------------------------------------------------------
    /// Helper functions
    const auto has = [&objects](const Shape* obj) {
      return std::find(objects->begin(), objects->end(), obj) != objects->end();
    };
    const auto remove = [&objects](const Shape* obj) {
      objects->erase(std::remove(objects->begin(), objects->end(), obj));
    };
    const auto add = [&objects](const Shape* obj) { objects->push_back(obj); };
    /// -----------------------------------------------------------------------

    for (const auto& intersection : xs->GetIntersectionPoints()) {
      const auto* object = i.object;

      if (intersection == *hit) {
        if (!objects->empty()) {
          comps.n1 = objects->back()->GetMaterial().refractiveIndex;
        }
      }

      if (has(object)) {
        remove(object);
      } else {
        add(object);
      }

      if (intersection == *hit) {
        if (!objects->empty()) {
          comps.n2 = objects->back()->GetMaterial().refractiveIndex;
        }
        break;
      }
    }
  }

  return comps;
}

float schlick(const Computations& comps)
{
  // find the cosine of the angle between the eye and normal vectors
  auto cos = dot(comps.eyev, comps.normalv);

  // total intenral reflection can only occur if n1 > n2
  if (comps.n1 > comps.n2) {
    auto n = comps.n1 / comps.n2;
    auto sin2_t = (n * n) * (1.0 - (cos * cos));
    if (sin2_t > 1.0) {
      return 1.0;
    }

    // compute cosine of theta_t using trig identity
    auto cos_t = std::sqrt(1.0 - sin2_t);

    // when n1 > n2, use cos(theta_t) instead
    cos = cos_t;
  }

  float r0 = std::pow(((comps.n1 - comps.n2) / (comps.n1 + comps.n2)), 2);
  return r0 + (1 - r0) * std::pow((1 - cos), 5);
}

} // namespace Lighting
} // namespace Rendering
} // namespace RayTracer
