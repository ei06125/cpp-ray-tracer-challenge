#include "RayTracer.hpp"

#include <memory>

using namespace RayTracer::Math;
using namespace RayTracer::Rendering;
using namespace RayTracer::Rendering::Lighting;
using namespace RayTracer::Rendering::Materials;
using namespace RayTracer::Rendering::Primitives;
using namespace RayTracer::Rendering::Cameras;
using namespace RayTracer::Rendering::Scene;

#ifdef NDEBUG
constexpr auto g_scale = 10;
#else
constexpr auto g_scale = 1;
#endif

int main()
{
  // world
  World world;

  // the floor
  auto floor = std::make_shared<Plane>();
  floor->SetTransform(scaling(10, 0.01, 10));
  floor->SetMaterial().color = make_color(1, 0.9, 0.9);
  floor->SetMaterial().specular = 0;
  world.AddObject(std::static_pointer_cast<Shape>(floor));

  // left wall
  auto left_wall = std::make_shared<Plane>();
  left_wall->SetTransform(translation(0, 0, 5) * rotation_y(-PI / 4) *
                          rotation_x(PI / 2) * scaling(10, 0.01, 10));
  left_wall->SetMaterial(floor->GetMaterial());
  world.AddObject(std::static_pointer_cast<Shape>(left_wall));

  // right wall
  auto right_wall = std::make_shared<Plane>();
  right_wall->SetTransform(translation(0, 0, 5) * rotation_y(PI / 4) *
                           rotation_x(PI / 2) * scaling(10, 0.01, 10));
  world.AddObject(std::static_pointer_cast<Shape>(right_wall));

  // large middle sphere
  auto middle = std::make_shared<Sphere>();
  middle->SetTransform(translation(-0.5, 1, 0.5));
  middle->SetMaterial().color = make_color(0.1, 1, 0.5);
  middle->SetMaterial().diffuse = 0.7;
  middle->SetMaterial().specular = 0.3;
  world.AddObject(std::static_pointer_cast<Shape>(middle));

  // small right sphere
  auto right = std::make_shared<Sphere>();
  right->SetTransform(translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5));
  right->SetMaterial().color = make_color(0.5, 1, 0.1);
  right->SetMaterial().diffuse = 0.7;
  right->SetMaterial().specular = 0.3;
  world.AddObject(std::static_pointer_cast<Shape>(right));

  // smallest left sphere
  auto left = std::make_shared<Sphere>();
  left->SetTransform(translation(-1.5, 0.33, -0.75) *
                     scaling(0.33, 0.33, 0.33));
  left->SetMaterial().color = make_color(1, 0.8, 0.1);
  left->SetMaterial().diffuse = 0.7;
  left->SetMaterial().specular = 0.3;
  world.AddObject(std::static_pointer_cast<Shape>(left));

  // light
  world.SetLight(PointLight{ Point(-10, 10, -10), make_color(1, 1, 1) });

  // camera
#ifdef NDEBUG
  auto camera = Camera{ 1000, 500, PI / 3 };
#else
  auto camera = Camera{ 100, 50, PI / 3 };
#endif

  camera.transform = view_transform(
    Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0));

  // render the result to a canvas.
  auto canvas = render(camera, world);

#ifdef NDEBUG
  PPMFile ppmFile("image.ppm");
#else
  PPMFile ppmFile("imaged.ppm");
#endif
  auto ppm = canvas_to_ppm(canvas);
  ppmFile.Write(ppm.c_str());

  return 0;
}
