#pragma once

#include "RayTracer/Rendering/Primitives/Shape.hpp"
#include "RayTracer/Rendering/RayTracing/Computations.hpp"
#include "RayTracer/Rendering/RayTracing/Intersection.hpp"
#include "RayTracer/Rendering/RayTracing/Light.hpp"

class World
{
public:
  std::vector<std::shared_ptr<Shape>>& GetObjects();
  std::vector<std::shared_ptr<Shape>> GetObjects() const;
  std::optional<PointLight> GetLightSource() const;
  void SetLight(PointLight p);
  void AddObject(std::shared_ptr<Shape> s);
  bool Contains(const std::shared_ptr<Shape> s) const;

private:
  std::vector<std::shared_ptr<Shape>> objects{};
  std::optional<PointLight> light{};
};

/// ===========================================================================
/// @section Functions
/// ===========================================================================

World default_world();

Intersections intersect_world(const World& w, const Ray& r);

Tuple shade_hit(const World& w, const Computations& comps);

Tuple color_at(const World& w, const Ray& r);

/// ===========================================================================
/// @section Shadows
/// ===========================================================================

bool is_shadowed(const World& w, const Tuple& p);
