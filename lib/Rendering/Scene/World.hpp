#pragma once

#include <optional>
#include <vector>

#include "Rendering/RayTracing/Intersection.hpp"
#include "Rendering/RayTracing/Light.hpp"
#include "Rendering/RayTracing/Sphere.hpp"

class World
{
public:
  std::vector<Sphere>& GetObjects();
  std::vector<Sphere> GetObjects() const;
  std::optional<PointLight> GetLightSource() const;
  void SetLight(PointLight p);
  void AddObject(Sphere s);
  bool Contains(const Sphere s) const;

private:
  std::vector<Sphere> objects{};
  std::optional<PointLight> light{};
};

/// ===========================================================================
/// @section Functions
/// ===========================================================================

World default_world();

Intersections intersect_world(const World& w, const Ray& r);

Tuple shade_hit(const World& w, const Computations& comps);

Tuple color_at(const World& w, const Ray& r);
