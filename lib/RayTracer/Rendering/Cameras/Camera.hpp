#pragma once

#include "RayTracer/Math/Matrix.hpp"
#include "RayTracer/Rendering/Canvas.hpp"
#include "RayTracer/Rendering/Lighting/Ray.hpp"
#include "RayTracer/Rendering/Scene/World.hpp"

namespace RayTracer {
namespace Rendering {
namespace Cameras {

using namespace Math;
using namespace Lighting;
using namespace Scene;

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

} // namespace Cameras
} // namespace Rendering
} // namespace RayTracer
