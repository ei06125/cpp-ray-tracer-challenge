#include "RayTracer/Rendering/Scene/World.hpp"

// Project Library
#include "RayTracer/Math/Transformations.hpp"
#include "RayTracer/Rendering/Primitives/Sphere.hpp"
#include "RayTracer/Rendering/RayTracing/Computations.hpp"

#include <algorithm>

std::vector<std::shared_ptr<Shape>>& World::GetObjects()
{
  return objects;
}

std::vector<std::shared_ptr<Shape>> World::GetObjects() const
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

  w.SetLight({ make_point(-10, 10, -10), make_color(1, 1, 1) });

  auto s1 = std::make_shared<Sphere>();
  Material newMaterial;
  newMaterial.color = make_color(0.8, 1.0, 0.6);
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

  for (const auto& object : w.GetObjects()) {
    auto intersections = object->Intersect(r);
    for (auto i = 0U; i < intersections.Count(); ++i) {
      result.Add(std::move(intersections[i]));
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

  return lighting(comps.object->GetMaterial(),
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
  auto theHit = intersections.Hit();

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

  if (auto hit = intersections.Hit(); hit != nullptr && hit->t < distance) {
    return true;
  }
  return false;
}