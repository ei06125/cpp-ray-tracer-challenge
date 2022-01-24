#include "RayTracer.hpp"

#include "Environment.hpp"
#include "Projectile.hpp"

inline auto toInt(auto x)
{
  return int(pow(clamp(x), 1 / 2.2) * 255 + .5);
}

Projectile tick(Environment env, Projectile proj)
{
  auto position = proj.position + proj.velocity;
  auto velocity = proj.velocity + env.gravity + env.wind;
  return Projectile{ position, velocity };
};

int main()
{
  auto start = make_point(0, 1, 0);
  auto velocity = normalize(make_vector(1, 1.8, 0)) * 11.25;
  auto p = Projectile{ start, velocity };

  auto gravity = make_vector(0, -0.1, 0);
  auto wind = make_vector(-0.01, 0, 0);
  auto e = Environment{ gravity, wind };

  auto w = 900;
  auto h = 550;
  auto c = Canvas(w, h);

  int ticks = 0;
  do {
    p = tick(e, p);

    write_pixel(c, p.position.x, h - p.position.y, make_color(1, 0, 0));

    Print("Projectile:", p);
    ticks++;
  } while (p.position.y > 0);

  Print("Took", ticks, "ticks to get to the ground");

  PPMFile ppmFile("image.ppm");
  auto ppm = canvas_to_ppm(c);
  ppmFile.Write(ppm.c_str());

  return 0;
}
