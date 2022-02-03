#include "RayTracerPCH.hpp"

// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"
#include "TestShape.hpp"

using namespace RayTracer::Rendering::Primitives;
using namespace RayTracer::Math;

SCENARIO("Creating a new group")
{
  GIVEN("g = group()")
  {
    auto g = Group();
    THEN("g.transform = identity_matrix\
        \n\t And g is empty")
    {
      CHECK(g.GetTransform() == mat4::Identity());
      CHECK(g.IsEmpty());
    }
  }
}

SCENARIO("Adding a child to a group")
{
  GIVEN("g = group()\
    \n\t And s = test_shape()")
  {
    auto g = std::make_shared<Group>();
    auto s = std::make_shared<::TestShape>();

    WHEN("add_child(g, s)")
    {
      g->AddChild(s);

      THEN("g includes s\
        \n\t And s.parent = g")
      {
        CHECK(g->Contains(s));
        CHECK(s->GetParent().lock().get() == g.get());
      }
    }
  }
}

SCENARIO("Intersecting a ray with an empty group")
{
  GIVEN("g = group()\
    \n\t And r = ray(point(0, 0, 0), vector(0, 0, 1))")
  {
    auto g = Group();
    auto r = Ray{ make_point(0, 0, 0), make_vector(0, 0, 1) };

    WHEN("xs = local_intersect(g, r)")
    {
      auto xs = g.Intersect(r);

      THEN("xs is empty") { CHECK(xs.Count() == 0); }
    }
  }
}

SCENARIO("Intersecting a ray with a nonempty group")
{
  GIVEN("g = group()\
    \n\t And s1 = sphere()\
    \n\t And s2 = sphere()\
    \n\t And set_transform(s2, translation(0, 0, -3)\
    \n\t And s3 = sphere()\
    \n\t And set_transform(s3, translation(5, 0, 0)\
    \n\t And add_child(g, s1)\
    \n\t And add_child(g, s2)\
    \n\t And add_child(g, s3)")
  {
    auto g = std::make_shared<Group>();
    auto s1 = std::make_shared<Sphere>();
    auto s2 = std::make_shared<Sphere>();
    s2->SetTransform(translation(0, 0, -3));
    auto s3 = std::make_shared<Sphere>();
    s3->SetTransform(translation(5, 0, 0));
    g->AddChild(s1);
    g->AddChild(s2);
    g->AddChild(s3);

    WHEN("r = ray(point(0, 0, -5), vector(0, 0, 1))\
      \n\t And xs = local_intersect(g, r)")
    {
      auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };
      auto xs = g->Intersect(r);

      THEN("xs.count == 4\
          \n\t And xs[0].object == s2\
          \n\t And xs[1].object == s2\
          \n\t And xs[2].object == s1\
          \n\t And xs[3].object == s1")
      {
        CHECK(xs.Count() == 4);
        CHECK(xs[0].object == s2.get());
        CHECK(xs[1].object == s2.get());
        CHECK(xs[2].object == s1.get());
        CHECK(xs[3].object == s1.get());
      }
    }
  }
}

SCENARIO("Intersecting a transformed group")
{
  GIVEN("g = group()\
  \n\t And set_transform(g, scaling(2, 2, 2))\
  \n\t And s = sphere()\
  \n\t And set_transform(s, translation(5, 0, 0))\
  \n\t And add_child(g, s)")
  {
    auto g = std::make_shared<Group>();
    g->SetTransform(scaling(2, 2, 2));
    auto s = std::make_shared<Sphere>();
    s->SetTransform(translation(5, 0, 0));
    g->AddChild(s);

    WHEN("r = ray(point(10, 0, -10), vector(0, 0, 1))\
    \n\t And xs = intersect(g, r)")
    {
      auto r = Ray{ make_point(10, 0, -10), make_vector(0, 0, 1) };
      auto xs = g->Intersect(r);

      THEN("xs.count == 2") { CHECK(xs.Count() == 2); }
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
      auto p = s->WorldToObject(make_point(-2, 0, -10));
      THEN("p == point(0, 0, -1)") { CHECK(p == make_point(0, 0, -1)); }
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
      auto n = s->NormalToWorld(make_vector(sqrt3 / 3, sqrt3 / 3, sqrt3 / 3));
      THEN("n == vector(0.2857, 0.4286, -0.8571)")
      {
        CHECK(n == make_vector(0.2857, 0.4286, -0.8571));
      }
    }
  }
}

SCENARIO("Finding a normal on a child object")
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

    WHEN("n = normal_at(s, point(1.7321, 1.1547, -5.5774))")
    {
      auto n = s->GetNormalAt(make_point(1.7321, 1.1547, -5.5774));
      THEN("n == vector(0.2857, 0.4286, -0.8571)")
      {
        CHECK(n == make_vector(0.2857, 0.4286, -0.8571));
      }
    }
  }
}
