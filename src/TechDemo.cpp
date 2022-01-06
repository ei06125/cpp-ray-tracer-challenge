#include "Environment.hpp"
#include "Projectile.hpp"
#include "Tuple.hpp"

#include <iostream>

template <typename T> class AddSpace {
private:
  T const &ref;

public:
  AddSpace(T const &r) : ref(r) {}
  friend std::ostream &operator<<(std::ostream &os, AddSpace<T> s) {
    return os << s.ref << ' ';
  }
};

template <typename... Args> void Print(Args... args) {
  (std::cout << ... << AddSpace(args)) << '\n';
}

Projectile tick(Environment env, Projectile proj) {
  auto position = proj.position + proj.velocity;
  auto velocity = proj.velocity + env.gravity + env.wind;
  return Projectile{position, velocity};
};

int main() {
  auto p = Projectile{make_point(0, 1, 0), normalize(make_vector(1, 1, 0))};
  auto e = Environment{make_vector(0, -0.1, 0), make_vector(-0.01, 0, 0)};
  int ticks = 0;
  do {
    p = tick(e, p);
    Print("Projectile:", p);
    ticks++;
  } while (p.position.y > 0);

  Print("Took", ticks, "ticks to get to the ground");

  return 0;
}
