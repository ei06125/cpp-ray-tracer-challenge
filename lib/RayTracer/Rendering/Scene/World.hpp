#pragma once
#include "RayTracerPCH.hpp"

#include "RayTracer/Rendering/Color.hpp"
#include "RayTracer/Rendering/Lighting/Computations.hpp"
#include "RayTracer/Rendering/Lighting/Intersection.hpp"
#include "RayTracer/Rendering/Lighting/Light.hpp"
#include "RayTracer/Rendering/Primitives/Shape.hpp"

namespace RayTracer {
namespace Rendering {
namespace Scene {
using namespace Math;
using namespace Primitives;
using namespace Lighting;
using namespace Colors;

class World
{
public:
  std::vector<std::shared_ptr<Shape>>& GetObjects();
  const std::vector<std::shared_ptr<Shape>>& GetObjects() const;
  std::optional<PointLight> GetLightSource() const;
  void SetLight(PointLight p);
  void AddObject(std::shared_ptr<Shape> s);
  bool Contains(const std::shared_ptr<Shape> s) const;

private:
  std::vector<std::shared_ptr<Shape>> objects{};
  std::optional<PointLight> light{};
};

World default_world();

Intersections intersect_world(const World& w, const Ray& r);

Color shade_hit(const World& w, const Computations& comps, int depth = 5);

Color color_at(const World& w, const Ray& r, int depth = 5);

bool is_shadowed(const World& w, const Tuple& p);

Color reflected_color(const World& w, const Computations& comps, int depth = 5);
Color refracted_color(const World& w, const Computations& comps, int depth = 5);

} // namespace Scene
} // namespace Rendering
} // namespace RayTracer
