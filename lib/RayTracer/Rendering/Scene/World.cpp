#include "RayTracer/Rendering/Scene/World.hpp"

// Project Library
#include "RayTracer/Math/Transformations.hpp"
#include "RayTracer/Rendering/Lighting/Computations.hpp"
#include "RayTracer/Rendering/Primitives/Sphere.hpp"

namespace RayTracer {
namespace Rendering {
namespace Scene {

using namespace Math;

std::vector<std::shared_ptr<Shape>>& World::GetObjects()
{
  return objects;
}

const std::vector<std::shared_ptr<Shape>>& World::GetObjects() const
{
  return objects;
}

std::optional<PointLight> World::GetLightSource() const
{
  return light;
}

void World::SetLight(PointLight aPointLight)
{
  light = aPointLight;
}

void World::AddObject(std::shared_ptr<Shape> s)
{
  objects.push_back(std::move(s));
}

bool World::Contains(const std::shared_ptr<Shape> s) const
{
  if (objects.empty()) {
    return false;
  }
  auto shapePtr = s.get();
  for (auto object : objects) {
    auto objectPtr = object.get();
    if (*objectPtr == *shapePtr) {
      return true;
    }
  }
  return false;
}

/// ===========================================================================
/// @section Functions
/// ===========================================================================

World default_world()
{
  World w;

  w.SetLight({ Point(-10, 10, -10), Color{ 1.0f, 1.0f, 1.0f } });

  auto s1 = std::make_shared<Sphere>();
  Material newMaterial;
  newMaterial.color = Color{ 0.8, 1.0, 0.6 };
  newMaterial.diffuse = 0.7;
  newMaterial.specular = 0.2;
  s1->SetMaterial(newMaterial);
  w.AddObject(std::static_pointer_cast<Shape>(s1));

  auto s2 = std::make_shared<Sphere>();
  s2->SetTransform(scaling(0.5, 0.5, 0.5));
  w.AddObject(std::static_pointer_cast<Shape>(s2));

  return w;
}

Intersections intersect_world(const World& w, const Ray& r)
{
  Intersections result;

  result.Reserve(w.GetObjects().size() * 2);
  for (const auto& object : w.GetObjects()) {
    auto intersections = object->Intersect(r);
    for (auto i = 0U; i < intersections.Count(); ++i) {
      result.EmplaceBack(std::move(intersections[i]));
    }
  }

  result.Sort();
  return result;
}

/// @todo Supporting Multiple Light Sources
Color shade_hit(const World& w, const Computations& comps, int depth)
{
  if (!w.GetLightSource()) {
    return Colors::Black;
  }

  const auto shadowed = is_shadowed(w, comps.over_point);

  auto surface = lighting(comps.object->GetMaterial(),
                          w.GetLightSource().value(),
                          comps.over_point,
                          comps.eyev,
                          comps.normalv,
                          shadowed,
                          comps.object);

  auto reflected = reflected_color(w, comps, depth);
  auto refracted = refracted_color(w, comps, depth);

  auto material = comps.object->GetMaterial();
  if (material.reflective > 0 && material.transparency > 0) {
    auto reflectance = schlick(comps);
    return surface + reflected * reflectance + refracted * (1 - reflectance);
  }
  return surface + reflected + refracted;
}

Color color_at(const World& w, const Ray& r, int depth)
{
  // find the intersections of the given ray with the given world
  const auto intersections = intersect_world(w, r);

  // Find the hit from the resulting intersections
  const auto* theHit = intersections.Hit();

  // Return the color black if there is no such intersection
  if (!theHit) {
    return Colors::Black;
  }

  // Otherwise, precompute the necessary values with prepare_computations
  const auto comps = prepare_computations(*theHit, r, &intersections);

  // Finally, call shade_hit to find the color at the hit
  return shade_hit(w, comps, depth);
}

/// ===========================================================================
/// @section Shadows
/// ===========================================================================

bool is_shadowed(const World& world, const Tuple& point)
{
  // if there is no light source, the Universe is in shadows
  if (!world.GetLightSource().has_value()) {
    return true;
  }

  const auto v = world.GetLightSource().value().position - point;
  const auto distance = magnitude(v);
  const auto direction = normalize(v);

  const auto ray = Ray{ point, direction };
  const auto intersections = intersect_world(world, ray);

  if (const auto hit = intersections.Hit();
      hit != nullptr && hit->t < distance) {
    return true;
  }
  return false;
}

/// ===========================================================================
/// @section Reflection
/// ===========================================================================

Color reflected_color(const World& w, const Computations& comps, int depth)
{
  // reflected color for a nonreflective material OR too many recursive calls
  if (comps.object->GetMaterial().reflective == 0 || depth < 1) {
    return Colors::Black;
  }

  auto reflect_ray = Ray{ comps.over_point, comps.reflectv };
  auto color = color_at(w, reflect_ray, depth - 1);
  return color * comps.object->GetMaterial().reflective;
}

Color refracted_color(const World& w, const Computations& comps, int depth)
{
  if (comps.object->GetMaterial().transparency == 0 || depth < 1) {
    return Colors::Black;
  }

  // Snell's Law:
  // Find the ratio of first index of refraction to the second.
  // (Yup, this is inverted from the definition of Snell's Law.)
  auto n_ratio = comps.n1 / comps.n2;

  // cos(theta_i) is the same as the dot product of the two vectors
  auto cos_i = dot(comps.eyev, comps.normalv);

  // Find sin(theta_t)^2 via trignometric identity
  auto sin2_t = (n_ratio * n_ratio) * (1 - (cos_i * cos_i));

  // if greater than 1, we got total internal reflection
  if (sin2_t > 1) {
    return Colors::Black;
  }

  // Find cos(theta_t) via trignometric identity
  auto cos_t = std::sqrt(1.0 - sin2_t);

  // Compute the direction of the refracted ray
  auto direction =
    comps.normalv * (n_ratio * cos_i - cos_t) - comps.eyev * n_ratio;

  // Create the refracted ray
  auto refracted_ray = Ray{ comps.under_point, direction };

  // Find the color of the refracted ray, making sure to multiply
  // by the transparency value to account for any opacity
  auto color = color_at(w, refracted_ray, depth - 1) *
               comps.object->GetMaterial().transparency;

  return color;
}

} // namespace Scene
} // namespace Rendering
} // namespace RayTracer
