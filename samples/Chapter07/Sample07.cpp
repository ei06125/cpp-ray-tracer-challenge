#include "Math/Constants.hpp"
#include "Math/Transformations.hpp"
#include "Rendering/Camera/Camera.hpp"
#include "Rendering/Canvas.hpp"
#include "Rendering/RayTracing/Intersection.hpp"
#include "Rendering/RayTracing/Light.hpp"
#include "Rendering/RayTracing/Material.hpp"
#include "Rendering/RayTracing/Ray.hpp"
#include "Rendering/RayTracing/Sphere.hpp"
#include "Rendering/Scene/World.hpp"
#include "Utils/PPMFile.hpp"
#include "Utils/Print.hpp"

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
  auto floor = Sphere();
  floor.transform = scaling(10, 0.01, 10);
  floor.material = Material();
  floor.material.color = make_color(1, 0.9, 0.9);
  floor.material.specular = 0;
  world.AddObject(floor);

  // left wall
  auto left_wall = Sphere();
  left_wall.transform = translation(0, 0, 5) * rotation_y(-PI / 4) *
                        rotation_x(PI / 2) * scaling(10, 0.01, 10);
  left_wall.material = floor.material;
  world.AddObject(left_wall);

  // right wall
  auto right_wall = Sphere();
  right_wall.transform = translation(0, 0, 5) * rotation_y(PI / 4) *
                         rotation_x(PI / 2) * scaling(10, 0.01, 10);
  world.AddObject(right_wall);

  // large middle sphere
  auto middle = Sphere();
  middle.transform = translation(-0.5, 1, 0.5);
  middle.material = Material();
  middle.material.color = make_color(0.1, 1, 0.5);
  middle.material.diffuse = 0.7;
  middle.material.specular = 0.3;
  world.AddObject(middle);

  // small right sphere
  auto right = Sphere();
  right.transform = translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5);
  right.material = Material();
  right.material.color = make_color(0.5, 1, 0.1);
  right.material.diffuse = 0.7;
  right.material.specular = 0.3;
  world.AddObject(right);

  // smallest left sphere
  auto left = Sphere();
  left.transform = translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33);
  left.material = Material();
  left.material.color = make_color(1, 0.8, 0.1);
  left.material.diffuse = 0.7;
  left.material.specular = 0.3;
  world.AddObject(left);

  // light
  world.SetLight(PointLight{ make_point(-10, 10, -10), make_color(1, 1, 1) });

  // camera
#ifdef NDEBUG
  auto camera = Camera{ 1000, 500, PI / 3 };
#else
  auto camera = Camera{ 100, 50, PI / 3 };
#endif

  camera.transform = view_transform(
    make_point(0, 1.5, -5), make_point(0, 1, 0), make_vector(0, 1, 0));

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
