#include "Rendering/Canvas.hpp"
#include "Rendering/RayTracing/Intersection.hpp"
#include "Rendering/RayTracing/Ray.hpp"
#include "Rendering/RayTracing/Sphere.hpp"
#include "Utils/PPMFile.hpp"

int main()
{
  // start the ray at z = -5
  auto ray_origin = make_point(0, 0, -5);

  // put the wall at z = 10
  auto wall_z = 10;

  auto wall_size = 7.0;
  auto canvas_pixels = 100;
  auto pixel_size = wall_size / canvas_pixels;
  auto half = wall_size / 2;

  auto canvas = Canvas(canvas_pixels, canvas_pixels);
  auto color = make_color(1, 0, 0);
  auto shape = Sphere();

#define TESTS 0
#if TESTS == 1
  // shrink it along the y axis
  shape.transform = scaling(1, 0.5, 1);
#elif TESTS == 2
  // shrink it along the x axis
  shape.transform = scaling(0.5, 1, 1);
#elif TESTS == 3
  // shrink it, and rotate it!
  shape.transform = rotation_z(M_PI / 4) * scaling(0.5, 1, 1);
#elif TESTS == 4
  // shrink it, and skew it!
  shape.transform = shearing(1, 0, 0, 0, 0, 0) * scaling(0.5, 1, 1);
#endif

  for (auto y = 0; y < canvas_pixels; ++y) {
    // compute the world y coordinate (top = +half, bottom = -half)
    auto world_y = half - pixel_size * y;

    // for each pixel in the row
    for (auto x = 0; x < canvas_pixels; ++x) {
      // compute the world x coordinate (left = -half, right = half)
      auto world_x = -half + pixel_size * x;

      // describe the point on the wall that the ray will target
      auto position = make_point(world_x, world_y, wall_z);

      auto r = Ray{ ray_origin, normalize(position - ray_origin) };
      auto xs = intersect(shape, r);

      if (hit(xs) != nullptr) {
        write_pixel(canvas, x, y, color);
      }
    }
  }

  PPMFile ppmFile("image.ppm");
  auto ppm = canvas_to_ppm(canvas);
  ppmFile.Write(ppm.c_str());

  return 0;
}
