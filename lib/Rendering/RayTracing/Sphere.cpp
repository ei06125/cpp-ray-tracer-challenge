#include "Rendering/RayTracing/Sphere.hpp"

std::size_t Sphere::SphereID = 0;

Sphere::Sphere()
  : transform(Matrix<4, 4>::Identity())
  , origin(make_point(0, 0, 0))
  , radius(1.0f)
  , id(SphereID++)
{}

bool operator==(const Sphere& lhs, const Sphere& rhs)
{
  return lhs.id == rhs.id;
}

void set_transform(Sphere& s, Matrix<4, 4> t)
{
  s.transform = t;
}
