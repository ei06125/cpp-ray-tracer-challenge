// Test Framework
#include "doctest/doctest.h"

// Project Library
#include "Math/Transformations.hpp"
#include "Rendering/RayTracing/Light.hpp"
#include "Rendering/RayTracing/Ray.hpp"
#include "Rendering/RayTracing/Sphere.hpp"
#include "Rendering/Scene/World.hpp"

// C++ Standard Library

SCENARIO("Creating a world")
{
  GIVEN("w = world()")
  {
    auto w = World();
    THEN("w contains no objects && w has no light source")
    {
      CHECK(w.GetObjects().empty());
      CHECK(!w.GetLightSource());
    }
  }
}

SCENARIO("The default world")
{
  GIVEN("light = point_light(point(-10, 10, -10), color(1, 1, 1))\
    \n AND s1 = sphere() with:\
    \n | material.color     | (0.8, 1.0, 0.6)   |\
    \n | material.diffuse   | 0.7               |\
    \n | material.specular  | 0.2               |\
    \n AND s2 = sphere() with:\
    \n | transform  | scaling(0.5, 0.5, 0.5) |")
  {
    auto light = PointLight{ make_point(-10, 10, -10), make_color(1, 1, 1) };

    auto s1 = Sphere();
    s1.material.color = make_color(0.8, 1.0, 0.6);
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;

    auto s2 = Sphere();
    set_transform(s2, scaling(0.5, 0.5, 0.5));

    WHEN("w = default_world()")
    {
      auto w = default_world();

      THEN("w.light == light && w contains s1 && w contains s2")
      {
        CHECK(w.GetLightSource() == light);
        CHECK(w.Contains(s1));
        CHECK(w.Contains(s2));
      }
    }
  }
}

SCENARIO("Intersect a world with a ray")
{
  GIVEN("w = default_world() && r = ray(point(0, 0, -5), vector(0, 0, 1))")
  {
    auto w = default_world();
    auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };

    WHEN("xs = intersect_world(w, r)")
    {
      auto xs = intersect_world(w, r);

      THEN("xs.count == 4 &&\
            \n xs[0].t == 4 &&\
            \n xs[1].t == 4.5 &&\
            \n xs[2].t == 5.5 &&\
            \n xs[3].t == 6 &&")
      {
        CHECK(xs.Count() == 4);
        CHECK(xs[0].t == 4);
        CHECK(xs[1].t == 4.5);
        CHECK(xs[2].t == 5.5);
        CHECK(xs[3].t == 6);
      }
    }
  }
}

SCENARIO("Shading an intersection")
{
  GIVEN("w = default_world() &&\
  \n r = ray(point(0, 0, -5), vector(0, 0, 1)) &&\
  \n shape = the first object in w &&\
  \n i = intersection(4, shape)")
  {
    auto w = default_world();
    auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };
    auto shape = w.GetObjects().front();
    auto i = Intersection(4, shape);

    WHEN("comps = prepare_computations(i, r) &&\
    \n c = shade_hit(w, comps)")
    {
      auto comps = prepare_computations(i, r);
      auto c = shade_hit(w, comps);

      THEN("c == color(0.38066, 0.47583, 0.2855)")
      {
        CHECK(c == make_color(0.38066, 0.47583, 0.2855));
      }
    }
  }
}

SCENARIO("Shading an intersection from the inside")
{
  GIVEN("w = default_world() &&\
  \n w.light = point_light(point(0, 0.25, 0), color(1, 1, 1)) &&\
  \n r = ray(point(0, 0, 0), vector(0, 0, 1)) &&\
  \n shape = the second object in w &&\
  \n i = intersection(0.5, shape)")
  {
    WHEN("comps = prepare_computations(i, r) &&\
    \n c = shade_hit(w, comps)")
    {
      THEN("c == color(0.90498, 0.90498, 0.90498)") { ; }
    }
  }
}

SCENARIO("The color when a ray misses")
{
  GIVEN("w = default_world && r = ray(point(0, 0, -5), vector(0, 1, 0))")
  {
    auto w = default_world();
    auto r = Ray{ make_point(0, 0, -5), make_vector(0, 1, 0) };

    WHEN("c = color_at(w, r)")
    {
      auto c = color_at(w, r);

      THEN("c == color(0, 0, 0)") { CHECK(c == make_color(0, 0, 0)); }
    }
  }
}

SCENARIO("The color when a ray hits")
{
  GIVEN("w = default_world && r = ray(point(0, 0, -5), vector(0, 0, 1))")
  {
    auto w = default_world();
    auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };

    WHEN("c = color_at(w, r)")
    {
      auto c = color_at(w, r);

      THEN("c == color(0.38066, 0.47583, 0.2855)")
      {
        CHECK(c == make_color(0.38066, 0.47583, 0.2855));
      }
    }
  }
}

SCENARIO("The color with an intersection behind the ray")
{
  GIVEN("w = default_world &&\
  \n outer = the first object in w &&\
  \n outer.material.ambient = 1 &&\
  \n inner = the second object in w &&\
  \n inner.material.ambient = 1 &&\
  \n r = ray(point(0, 0, 0.75), vector(0, 0, -1))")
  {
    auto w = default_world();
    auto& outer = w.GetObjects()[0];
    outer.material.ambient = 1;
    auto& inner = w.GetObjects()[1];
    inner.material.ambient = 1;
    auto r = Ray{ make_point(0, 0, 0.75), make_vector(0, 0, -1) };

    WHEN("c = color_at(w, r)")
    {
      auto c = color_at(w, r);
      THEN("c == inner.material.color") { CHECK(c == inner.material.color); }
    }
  }
}