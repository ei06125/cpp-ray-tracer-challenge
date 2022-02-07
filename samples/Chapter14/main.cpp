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

std::shared_ptr<Sphere> HexagonCorner()
{
  auto corner = std::make_shared<Sphere>();
  corner->SetTransform(translation(0, 0, -1) * scaling(0.25, 0.25, 0.25));
  return corner;
}

std::shared_ptr<Cylinder> HexagonEdge()
{
  auto edge = std::make_shared<Cylinder>();
  edge->SetMinimum(0);
  edge->SetMaximum(1);
  edge->SetTransform(translation(0, 0, -1) * rotation_y(-PI / 6) *
                     rotation_z(-PI / 2) * scaling(0.25, 1, 0.25));
  return edge;
}

std::shared_ptr<Group> HexagonSide()
{
  auto side = std::make_shared<Group>();
  side->AddChild(HexagonCorner());
  side->AddChild(HexagonEdge());
  return side;
}

std::shared_ptr<Group> Hexagon()
{
  auto hex = std::make_shared<Group>();
  for (auto n = 0; n <= 5; ++n) {
    auto side = HexagonSide();
    side->SetTransform(rotation_y(n * PI / 3));
    hex->AddChild(side);
  }
  return hex;
}

int main()
{
  TrackNew::reset();

  // world
  World world;

  // light
  world.SetLight(PointLight{ Point(-10, 10, -10), Color{ 1.0f, 1.0f, 1.0f } });

  // the floor
  auto floor = std::make_shared<Plane>();
  floor->SetTransform(translation(0, -2, 0) * scaling(10, 0.01, 10));
  floor->SetMaterial().color = Color{ 1.0f, 0.9f, 0.9f };
  floor->SetMaterial().specular = 0;
  world.AddObject(floor);

  auto hex = Hexagon();
  world.AddObject(hex);

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
