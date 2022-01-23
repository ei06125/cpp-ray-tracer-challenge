#pragma once

#include "Math/Matrix.hpp"
#include "Rendering/Canvas.hpp"
#include "Rendering/RayTracing/Ray.hpp"
#include "Rendering/Scene/World.hpp"

struct Camera
{
  Camera(float h, float v, float fov);
  mat4 transform;
  float hsize;
  float vsize;
  float field_of_view;
  float pixel_size;
  float half_width;
  float half_height;
};

Ray ray_for_pixel(const Camera& c, float px, float py);

Canvas render(const Camera& c, const World& w);
