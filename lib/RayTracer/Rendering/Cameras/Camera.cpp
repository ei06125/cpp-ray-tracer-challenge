#include "RayTracer/Rendering/Cameras/Camera.hpp"

namespace RayTracer::Rendering::Cameras {
using namespace Math;

Camera::Camera(float h, float v, float fov)
  : transform(mat4::Identity())
  , hsize(h)
  , vsize(v)
  , field_of_view(fov)
{
  auto half_view = std::tan(fov / 2);
  auto aspectRatio = hsize / vsize;
  if (aspectRatio >= 1) {
    half_width = half_view;
    half_height = half_view / aspectRatio;
  } else {
    half_width = half_view * aspectRatio;
    half_height = half_view;
  }
  pixel_size = (half_width * 2) / hsize;
}

Ray ray_for_pixel(const Camera& c, float px, float py)
{
  // the offset from the edge of the canvas to the pixel's center
  auto xoffset = (px + 0.5) * c.pixel_size;
  auto yoffset = (py + 0.5) * c.pixel_size;

  // the unstransformed coordinates of the pixel in world space.
  // (remember that the camera looks toward -z, so +x is to the *leflt*.)
  auto world_x = c.half_width - xoffset;
  auto world_y = c.half_height - yoffset;

  // using the camera matrix, transform the canvas point and the origin,
  // and then compute the ray's direction vector.
  // (remember that the canvas is at z=-1)
  auto pixel = inverse(c.transform) * make_point(world_x, world_y, -1);
  auto origin = inverse(c.transform) * make_point(0, 0, 0);
  auto direction = normalize(pixel - origin);

  return { origin, direction };
}

Canvas render(const Camera& camera, const World& world)
{
  auto image = Canvas(camera.hsize, camera.vsize);
  const int hsize = camera.hsize;
  const int vsize = camera.vsize;

#if defined(_OPENMP)
#pragma omp parallel for schedule(dynamic, 1) shared(camera, world, image)
#endif
  for (int y = 0; y < vsize; ++y) {
    for (int x = 0; x < hsize; ++x) {
      const auto ray = ray_for_pixel(camera, x, y);
      const auto color = color_at(world, ray);
      write_pixel(image, x, y, color);
    }
  }

  return image;
}

} // namespace RayTracer::Rendering::Cameras
