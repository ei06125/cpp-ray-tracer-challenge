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
constexpr auto g_scale = 2;
#endif

int main()
{
  // world
  World world;

  // the floor
  auto floor = std::make_shared<Sphere>();
  floor->SetTransform(scaling(10, 0.01, 10));
  floor->SetMaterial().color = make_color(1, 0.9, 0.9);
  floor->SetMaterial().specular = 0;
  world.AddObject(floor);

  // left wall
  auto left_wall = std::make_shared<Sphere>();
  left_wall->SetTransform(translation(0, 0, 5) * rotation_y(-PI / 4) *
                          rotation_x(PI / 2) * scaling(10, 0.01, 10));
  left_wall->SetMaterial(floor->GetMaterial());
  world.AddObject(left_wall);

  // right wall
  auto right_wall = std::make_shared<Sphere>();
  right_wall->SetTransform(translation(0, 0, 5) * rotation_y(PI / 4) *
                           rotation_x(PI / 2) * scaling(10, 0.01, 10));
  world.AddObject(right_wall);

  // large middle sphere
  auto middleSphere = std::make_shared<Sphere>();
  middleSphere->SetTransform(translation(-0.5, 1, 0.5));
  middleSphere->SetMaterial().color = make_color(0.1, 1, 0.5);
  middleSphere->SetMaterial().diffuse = 0.7;
  middleSphere->SetMaterial().specular = 0.3;
  world.AddObject(middleSphere);

  // small right sphere
  auto rightSphere = std::make_shared<Sphere>();
  rightSphere->SetTransform(translation(1.5, 0.5, -0.5) *
                            scaling(0.5, 0.5, 0.5));
  rightSphere->SetMaterial().color = make_color(0.5, 1, 0.1);
  rightSphere->SetMaterial().diffuse = 0.7;
  rightSphere->SetMaterial().specular = 0.3;
  world.AddObject(rightSphere);

  // smallest left sphere
  auto leftSphere = std::make_shared<Sphere>();
  leftSphere->SetTransform(translation(-1.5, 0.33, -0.75) *
                           scaling(0.33, 0.33, 0.33));
  leftSphere->SetMaterial().color = make_color(1, 0.8, 0.1);
  leftSphere->SetMaterial().diffuse = 0.7;
  leftSphere->SetMaterial().specular = 0.3;
  world.AddObject(leftSphere);

  // light
  world.SetLight(PointLight{ make_point(-10, 10, -10), make_color(1, 1, 1) });

  // camera
#ifdef NDEBUG
  // High-Definition 16:9
  auto camera = Camera{ 1280, 720, PI / 3 };
#else
  // Low-Definition 16:9
  auto camera = Camera{ 426, 240, PI / 3 };
#endif

  camera.transform = view_transform(
    make_point(0, 1.5, -5), make_point(0, 1, 0), make_vector(0, 1, 0));

  /// =========================================================================
  /// @section Rendering
  /// =========================================================================

  // render the result to a canvas.
  Timer renderTimer("to render");
  auto canvas = render(camera, world);
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
