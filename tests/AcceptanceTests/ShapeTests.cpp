// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"
#include "TestShape.hpp"

using namespace RayTracer::Rendering::Primitives;
using namespace RayTracer::Rendering::Lighting;
using namespace RayTracer::Math;

SCENARIO("A shape's default transformation")
{
  GIVEN("s = shape()")
  {
    auto s = TestShape();

    THEN("s.transform == identity_matrix")
    {
      CHECK(s.GetTransform() == mat4::Identity());
    }
  }
}

SCENARIO("Changing a shape's transformation")
{
  GIVEN("s = shape() && t = translation(2, 3, 4)")
  {
    auto s = TestShape();
    auto t = translation(2, 3, 4);

    WHEN("set_transform(s, t)")
    {
      s.SetTransform(t);

      THEN("s.transform == t") { CHECK(s.GetTransform() == t); }
    }
  }
}

SCENARIO("A shape has a default material")
{
  GIVEN("s = shape()")
  {
    auto s = TestShape();

    WHEN("m = s.material")
    {
      auto m = s.GetMaterial();

      THEN("m == material()") { CHECK(m == Material()); }
    }
  }
}

SCENARIO("A shape may be assigned a material")
{
  GIVEN("s = shape() && m = material() && m.ambient = 1")
  {
    auto s = TestShape();
    auto m = Material();
    m.ambient = 1;

    WHEN("s.material = m")
    {
      s.SetMaterial(m);

      THEN("s.material == m") { CHECK(s.GetMaterial() == m); }
    }
  }
}

SCENARIO("Intersecting a scaled shape with a ray")
{
  GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1)) && s = shape()")
  {
    auto r = Ray{ Point(0, 0, -5), Vector(0, 0, 1) };
    auto s = TestShape();

    WHEN("set_transform(s, scaling(2, 2, 2)) && xs = intersect(s, r)")
    {
      s.SetTransform(scaling(2, 2, 2));
      auto xs = s.Intersect(r);

      THEN("s.saved_ray.origin == point(0, 0, -2.5) &&\
      \n s.saved_ray.direction == vector(0, 0, 0.5)")
      {
        CHECK(s.saved_ray.origin == Point(0, 0, -2.5));
        CHECK(s.saved_ray.direction == Vector(0, 0, 0.5));
      }
    }
  }
}

SCENARIO("Intersecting a translated shape with a ray")
{
  GIVEN("r = ray(point(0, 0, -5), vector(0, 0, 1)) && s = shape()")
  {
    auto r = Ray{ Point(0, 0, -5), Vector(0, 0, 1) };
    auto s = TestShape();

    WHEN("set_transform(s, scaling(2, 2, 2)) && xs = intersect(s, r)")
    {
      s.SetTransform(translation(5, 0, 0));
      auto xs = s.Intersect(r);

      THEN("s.saved_ray.origin == point(-5, 0,  -5) &&\
      \n s.saved_ray.direction == vector(0, 0, 1)")
      {
        CHECK(s.saved_ray.origin == Point(-5, 0, -5));
        CHECK(s.saved_ray.direction == Vector(0, 0, 1));
      }
    }
  }
}

SCENARIO("Computing the normal on a translated shape")
{
  GIVEN("s = shape() && set_transform(s, translation(0, 1, 0))")
  {
    auto s = TestShape();
    s.SetTransform(translation(0, 1, 0));

    WHEN("n = normal_at(s, point(0, 1.70711, -0.70711))")
    {
      auto n = s.GetNormalAt(Point(0, 1.70711, -0.70711));

      THEN("n == vector(0, 0.70711, -0.70711)")
      {
        CHECK(n == Vector(0, 0.70711, -0.70711));
      }
    }
  }
}

SCENARIO("Computing the normal on a transformed shape")
{
  GIVEN("s = shape() &&\
  \n m = scaling(1, 0.5, 1) * rotation_z(PI/5) &&\
  \n set_transform(s, translation(0, 1, 0))")
  {
    auto s = TestShape();
    auto matrix = scaling(1, 0.5, 1) * rotation_z(PI / 5);
    s.SetTransform(matrix);

    WHEN("n = normal_at(s, point(0, SQRT(2)/2, -SQRT(2)/2))")
    {
      auto sqrt2 = std::sqrt(2);
      auto sqrt2over2 = sqrt2 / 2;
      auto n = s.GetNormalAt(Point(0, sqrt2over2, -sqrt2over2));

      THEN("n == vector(0, 0.97014, -0.24254)")
      {
        CHECK(n == Vector(0, 0.97014, -0.24254));
      }
    }
  }
}

SCENARIO("Converting a point from world to object space")
{
  GIVEN("g1 = group()\
  \n\t And set_transform(g1, rotation_y(PI/2))\
  \n\t And g2 = group()\
  \n\t And set_transform(g2, scaling(2, 2, 2))\
  \n\t And add_child(g1, g2)\
  \n\t And s = sphere()\
  \n\t And set_transform(s, translation(5, 0, 0))\
  \n\t And add_child(g2, s)")
  {
    auto g1 = std::make_shared<Group>();
    g1->SetTransform(rotation_y(PI / 2));
    auto g2 = std::make_shared<Group>();
    g2->SetTransform(scaling(2, 2, 2));
    g1->AddChild(g2);
    auto s = std::make_shared<Sphere>();
    s->SetTransform(translation(5, 0, 0));
    g2->AddChild(s);

    WHEN("p = world_to_object(s, point(-2, 0, -10))")
    {
      auto p = s->WorldToObject(Point(-2, 0, -10));
      THEN("p == point(0, 0, -1)") { CHECK(p == Point(0, 0, -1)); }
    }
  }
}

SCENARIO("Converting a normal from object to world space")
{
  GIVEN("g1 = group()\
  \n\t And set_transform(g1, rotation_y(PI/2))\
  \n\t And g2 = group()\
  \n\t And set_transform(g2, scaling(1, 2, 3))\
  \n\t And add_child(g1, g2)\
  \n\t And s = sphere()\
  \n\t And set_transform(s, translation(5, 0, 0))\
  \n\t And add_child(g2, s)")
  {
    auto g1 = std::make_shared<Group>();
    g1->SetTransform(rotation_y(PI / 2));
    auto g2 = std::make_shared<Group>();
    g2->SetTransform(scaling(1, 2, 3));
    g1->AddChild(g2);
    auto s = std::make_shared<Sphere>();
    s->SetTransform(translation(5, 0, 0));
    g2->AddChild(s);

    WHEN("n = normal_to_world(s, vector(SQRT(3)/3, SQRT(3)/3, SQRT(3)/3))")
    {
      float sqrt3 = std::sqrt(3);
      auto n = s->NormalToWorld(Vector(sqrt3 / 3, sqrt3 / 3, sqrt3 / 3));
      THEN("n == vector(0.2857, 0.4286, -0.8571)")
      {
        CHECK(n == Vector(0.2857, 0.4286, -0.8571));
      }
    }
  }
}
