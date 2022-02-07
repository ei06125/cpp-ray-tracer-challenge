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

int main()
{
  TrackNew::reset();

  // world
  World world;

  // the floor
  auto floor = std::make_shared<Plane>();
  floor->SetTransform(scaling(10, 0.01, 10));
  floor->SetMaterial().color = Color{ 1, 0.9, 0.9 };
  floor->SetMaterial().specular = 0;
  world.AddObject(floor);

  // left wall
  auto left_wall = std::make_shared<Plane>();
  left_wall->SetTransform(translation(0, 0, 5) * rotation_y(-PI / 4) *
                          rotation_x(PI / 2) * scaling(10, 0.01, 10));
  left_wall->SetMaterial(floor->GetMaterial());
  world.AddObject(left_wall);

  // right wall
  auto right_wall = std::make_shared<Plane>();
  right_wall->SetTransform(translation(0, 0, 5) * rotation_y(PI / 4) *
                           rotation_x(PI / 2) * scaling(10, 0.01, 10));
  right_wall->SetTransform(scaling(10, 0.01, 10));
  right_wall->SetMaterial().color = Color{ 1, 0.9, 0.9 };
  right_wall->SetMaterial().specular = 0;
  world.AddObject(std::static_pointer_cast<Shape>(right_wall));

  // large middle sphere
  auto middle_sphere = std::make_shared<Sphere>();
  middle_sphere->SetTransform(translation(-0.5, 1, 0.5));
  middle_sphere->SetMaterial().color = Color{ 0.1, 1, 0.5 };
  middle_sphere->SetMaterial().diffuse = 0.7;
  middle_sphere->SetMaterial().specular = 0.3;
  world.AddObject(middle_sphere);

  // small right sphere
  auto right_sphere = std::make_shared<Sphere>();
  right_sphere->SetTransform(translation(1.5, 0.5, -0.5) *
                             scaling(0.5, 0.5, 0.5));
  right_sphere->SetMaterial().color = Color{ 0.5, 1, 0.1 };
  right_sphere->SetMaterial().diffuse = 0.7;
  right_sphere->SetMaterial().specular = 0.3;
  world.AddObject(right_sphere);

  // smallest left sphere
  auto left_sphere = std::make_shared<Sphere>();
  left_sphere->SetTransform(translation(-1.5, 0.33, -0.75) *
                            scaling(0.33, 0.33, 0.33));
  left_sphere->SetMaterial().color = Color{ 1, 0.8, 0.1 };
  left_sphere->SetMaterial().diffuse = 0.7;
  left_sphere->SetMaterial().specular = 0.3;
  world.AddObject(left_sphere);

  // light
  world.SetLight(PointLight{ Point(-10, 10, -10), Color{ 1, 1, 1 } });

// camera
#ifdef NDEBUG
  // High-Definition 16:9
  auto camera = Camera{ 1280, 720, PI / 3 };
#else
  // Low-Definition 16:9
  auto camera = Camera{ 426, 240, PI / 3 };
#endif
  camera.transform =
    view_transform(Point(0, 2.5, -10), Point(0, 1, 0), Vector(0, 1, 0));

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
