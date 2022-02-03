#include "RayTracer.hpp"

using namespace RayTracer::Math;

using namespace RayTracer::Rendering;
using namespace RayTracer::Rendering::Lighting;
using namespace RayTracer::Rendering::Materials;
using namespace RayTracer::Rendering::Primitives;
using namespace RayTracer::Rendering::Patterns;
using namespace RayTracer::Rendering::Cameras;
using namespace RayTracer::Rendering::Scene;

using namespace RayTracer::Profiling;

#ifdef NDEBUG
constexpr auto g_scale = 10;
#else
constexpr auto g_scale = 5;
#endif

int main()
{
  // start the ray at z = -5
  auto ray_origin = make_point(0, 0, -5 * g_scale);

  // put the wall at z = 10
  auto wall_z = 10 * g_scale;

  auto wall_size = 7.0 * g_scale;
  auto canvas_pixels = 100 * g_scale;
  auto pixel_size = wall_size / canvas_pixels;
  auto half = wall_size / 2;

  auto canvas = Canvas(canvas_pixels, canvas_pixels);
  auto color = make_color(1, 0, 0);
  auto sphere = Sphere();
  sphere.SetTransform(scaling(1 * g_scale, 1 * g_scale, 1 * g_scale));
  sphere.SetMaterial().color = make_color(1, 0.2, 1);

  auto light_position = make_point(-10 * g_scale, 10 * g_scale, -10 * g_scale);
  auto light_color = make_color(1, 1, 1);
  auto light = PointLight{ light_position, light_color };

  Timer renderTimer("to render");
  for (auto y = 0; y < canvas_pixels; ++y) {
    // compute the world y coordinate (top = +half, bottom = -half)
    auto world_y = half - pixel_size * y;

    // for each pixel in the row
    for (auto x = 0; x < canvas_pixels; ++x) {
      // compute the world x coordinate (left = -half, right = half)
      auto world_x = -half + pixel_size * x;

      // describe the point on the wall that the ray will target
      auto wall_point = make_point(world_x, world_y, wall_z);

      auto r = Ray{ ray_origin, normalize(wall_point - ray_origin) };
      auto xs = sphere.Intersect(r);

      if (auto aHit = xs.Hit(); aHit != nullptr) {
        auto material = aHit->object->GetMaterial();
        auto point = position(r, aHit->t);
        auto normalv = aHit->object->GetNormalAt(point);
        auto eyev = -(r.direction); // negated
        color = lighting(material, light, point, eyev, normalv);

        write_pixel(canvas, x, y, color);
      }
    }
  }
  renderTimer.status();

  /// =========================================================================
  /// @section Saving
  /// =========================================================================

  std::string filename = "image";
#ifndef NDEBUG
  filename += "d";
#endif
  filename += "_";
  const std::chrono::time_point<std::chrono::system_clock> now =
    std::chrono::system_clock::now();
  const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
  filename += std::to_string(std::localtime(&t_c)->tm_hour) + "_";
  filename += std::to_string(std::localtime(&t_c)->tm_min) + "_";
  filename += std::to_string(std::localtime(&t_c)->tm_sec) + "_";
  filename += ".ppm";

  PPMFile ppmFile(filename.c_str());
  auto ppm = canvas_to_ppm(canvas);
  ppmFile.Write(ppm.c_str());

  return 0;
}
