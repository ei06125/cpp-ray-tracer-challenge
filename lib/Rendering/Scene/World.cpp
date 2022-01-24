#include "Rendering/Scene/World.hpp"

// Project Library
#include "Math/Transformations.hpp"

std::vector<Sphere>& World::GetObjects()
{
  return objects;
}

std::vector<Sphere> World::GetObjects() const
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

void World::AddObject(Sphere s)
{
  objects.push_back(std::move(s));
}

bool World::Contains(const Sphere s) const
{
  if (objects.empty()) {
    return false;
  }
  auto found = std::find(objects.cbegin(), objects.cend(), s);
  return found != objects.cend();
}

/// ===========================================================================
/// @section Functions
/// ===========================================================================

World default_world()
{
  World w;

  w.SetLight({ make_point(-10, 10, -10), make_color(1, 1, 1) });

  Sphere s1;
  s1.material.color = make_color(0.8, 1.0, 0.6);
  s1.material.diffuse = 0.7;
  s1.material.specular = 0.2;
  w.AddObject(s1);

  Sphere s2;
  set_transform(s2, scaling(0.5, 0.5, 0.5));
  w.AddObject(s2);

  return w;
}

#include <algorithm>
Intersections intersect_world(const World& w, const Ray& r)
{
  Intersections result;
  for (const auto& object : w.GetObjects()) {
    const auto intersections = intersect(object, r);
    for (auto i = 0U; i < intersections.Count(); ++i) {
      result.Push(std::move(intersections[i]));
    }
  }
  auto& intersectionPoints = result.GetIntersectionPoints();
  std::sort(intersectionPoints.begin(), intersectionPoints.end());
  return result;
}

/// @todo Supporting Multiple Light Sources
Tuple shade_hit(const World& w, const Computations& comps)
{
  if (!w.GetLightSource()) {
    return make_color(0, 0, 0); // black
  }
  auto shadowed = is_shadowed(w, comps.over_point);

  return lighting(comps.object.material,
                  w.GetLightSource().value(),
                  comps.point,
                  comps.eyev,
                  comps.normalv,
                  shadowed);
}

Tuple color_at(const World& w, const Ray& r)
{
  // find the intersections of the given ray with the given world
  auto intersections = intersect_world(w, r);

  // Find the hit from the resulting intersections
  auto theHit = hit(intersections);

  // Return the color black if there is no such intersection
  if (!theHit) {
    return make_color(0, 0, 0);
  }
  // Otherwise, precompute the necessary values with prepare_computations
  auto comps = prepare_computations(*theHit, r);

  // Finally, call shade_hit to find the color at the hit
  return shade_hit(w, comps);
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

  auto v = world.GetLightSource().value().position - point;
  auto distance = magnitude(v);
  auto direction = normalize(v);

  auto ray = Ray{ point, direction };
  auto intersections = intersect_world(world, ray);

  if (auto h = hit(intersections); h != nullptr && h->t < distance) {
    return true;
  }
  return false;
}
