#include "RayTracer.hpp"

int main()
{
  constexpr auto width = 720;
  constexpr auto height = 720;
  constexpr auto radius = 720 / 4;

  const auto color = make_color(1, 0, 0);

  auto canvas = Canvas(width, height);
  auto p = Point(0, radius, 0);
  auto angle = std::numbers::pi / 6;
  auto translate = translation(width / 2, height / 2, 0);

  for (auto hour = 0; hour < 12; ++hour) {
    auto clock = rotation_z(-angle * hour);
    auto point = translate * clock * p;
    Print(hour, ":", point);
    write_pixel(canvas, point.x, point.y, color);
  }

  PPMFile ppmFile("image.ppm");
  auto ppm = canvas_to_ppm(canvas);
  ppmFile.Write(ppm.c_str());

  return 0;
}
