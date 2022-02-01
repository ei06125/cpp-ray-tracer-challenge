// // Test Framework
// #include "doctest/doctest.h"

// // Engine
// #include "RayTracer.hpp"

// using namespace RayTracer::Rendering::Scene;
// using namespace RayTracer::Rendering::Lighting;
// using namespace RayTracer::Math;

// SCENARIO("Creating a world")
// {
//   GIVEN("w = world()")
//   {
//     auto w = World();
//     THEN("w contains no objects && w has no light source")
//     {
//       CHECK(w.GetObjects().empty());
//       CHECK(!w.GetLightSource());
//     }
//   }
// }

// SCENARIO("The default world")
// {
//   GIVEN("light = point_light(point(-10, 10, -10), color(1, 1, 1))\
//     \n AND s1 = sphere() with:\
//     \n | material.color     | (0.8, 1.0, 0.6)   |\
//     \n | material.diffuse   | 0.7               |\
//     \n | material.specular  | 0.2               |\
//     \n AND s2 = sphere() with:\
//     \n | transform  | scaling(0.5, 0.5, 0.5) |")
//   {
//     auto light = PointLight{ make_point(-10, 10, -10), make_color(1, 1, 1) };

//     auto s1 = std::make_shared<Sphere>();
//     auto m1 = Material();
//     m1.color = make_color(0.8, 1.0, 0.6);
//     m1.diffuse = 0.7;
//     m1.specular = 0.2;
//     s1->SetMaterial(m1);

//     auto s2 = std::make_shared<Sphere>();
//     s2->SetTransform(scaling(0.5, 0.5, 0.5));

//     WHEN("w = default_world()")
//     {
//       auto w = default_world();

//       THEN("w.light == light && w contains s1 && w contains s2")
//       {
//         CHECK(w.GetLightSource() == light);
//         CHECK(w.Contains(std::static_pointer_cast<Shape>(s1)));
//         CHECK(w.Contains(std::static_pointer_cast<Shape>(s2)));
//       }
//     }
//   }
// }

// SCENARIO("Intersect a world with a ray")
// {
//   GIVEN("w = default_world() && r = ray(point(0, 0, -5), vector(0, 0, 1))")
//   {
//     auto w = default_world();
//     auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };

//     WHEN("xs = intersect_world(w, r)")
//     {
//       auto xs = intersect_world(w, r);

//       THEN("xs.count == 4 &&\
//             \n xs[0].t == 4 &&\
//             \n xs[1].t == 4.5 &&\
//             \n xs[2].t == 5.5 &&\
//             \n xs[3].t == 6 &&")
//       {
//         CHECK(xs.Count() == 4);
//         CHECK(xs[0].t == 4);
//         CHECK(xs[1].t == 4.5);
//         CHECK(xs[2].t == 5.5);
//         CHECK(xs[3].t == 6);
//       }
//     }
//   }
// }

// SCENARIO("Shading an intersection")
// {
//   GIVEN("w = default_world() &&\
//   \n r = ray(point(0, 0, -5), vector(0, 0, 1)) &&\
//   \n shape = the first object in w &&\
//   \n i = intersection(4, shape)")
//   {
//     auto w = default_world();
//     auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };
//     auto shape = w.GetObjects().front();
//     auto i = Intersection(4, shape.get());

//     WHEN("comps = prepare_computations(i, r) &&\
//     \n c = shade_hit(w, comps)")
//     {
//       auto comps = prepare_computations(i, r);
//       auto c = shade_hit(w, comps);

//       THEN("c == color(0.38066, 0.47583, 0.2855)")
//       {
//         CHECK(c == make_color(0.38066, 0.47583, 0.2855));
//       }
//     }
//   }
// }

// SCENARIO("Shading an intersection from the inside")
// {
//   GIVEN("w = default_world() &&\
//   \n w.light = point_light(point(0, 0.25, 0), color(1, 1, 1)) &&\
//   \n r = ray(point(0, 0, 0), vector(0, 0, 1)) &&\
//   \n shape = the second object in w &&\
//   \n i = intersection(0.5, shape)")
//   {
//     auto w = default_world();
//     w.SetLight(PointLight{ make_point(0, 0.25, 0), make_color(1, 1, 1) });
//     auto r = Ray{ make_point(0, 0, 0), make_vector(0, 0, 1) };
//     auto shape = w.GetObjects().at(1);
//     auto i = Intersection(0.5, shape.get());

//     WHEN("comps = prepare_computations(i, r) &&\
//     \n c = shade_hit(w, comps)")
//     {
//       auto comps = prepare_computations(i, r);
//       auto c = shade_hit(w, comps);

//       THEN("c == color(0.90498, 0.90498, 0.90498)")
//       {
//         CHECK(c == make_color(0.90498, 0.90498, 0.90498));
//       }
//     }
//   }
// }

// SCENARIO("The color when a ray misses")
// {
//   GIVEN("w = default_world && r = ray(point(0, 0, -5), vector(0, 1, 0))")
//   {
//     auto w = default_world();
//     auto r = Ray{ make_point(0, 0, -5), make_vector(0, 1, 0) };

//     WHEN("c = color_at(w, r)")
//     {
//       auto c = color_at(w, r);

//       THEN("c == color(0, 0, 0)") { CHECK(c == make_color(0, 0, 0)); }
//     }
//   }
// }

// SCENARIO("The color when a ray hits")
// {
//   GIVEN("w = default_world && r = ray(point(0, 0, -5), vector(0, 0, 1))")
//   {
//     auto w = default_world();
//     auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };

//     WHEN("c = color_at(w, r)")
//     {
//       auto c = color_at(w, r);

//       THEN("c == color(0.38066, 0.47583, 0.2855)")
//       {
//         CHECK(c == make_color(0.38066, 0.47583, 0.2855));
//       }
//     }
//   }
// }

// SCENARIO("The color with an intersection behind the ray")
// {
//   GIVEN("w = default_world &&\
//   \n outer = the first object in w &&\
//   \n outer.material.ambient = 1 &&\
//   \n inner = the second object in w &&\
//   \n inner.material.ambient = 1 &&\
//   \n r = ray(point(0, 0, 0.75), vector(0, 0, -1))")
//   {
//     auto w = default_world();
//     auto& outer = w.GetObjects()[0];
//     outer->SetMaterial().ambient = 1;
//     auto& inner = w.GetObjects()[1];
//     inner->SetMaterial().ambient = 1;
//     auto r = Ray{ make_point(0, 0, 0.75), make_vector(0, 0, -1) };

//     WHEN("c = color_at(w, r)")
//     {
//       auto c = color_at(w, r);
//       THEN("c == inner.material.color")
//       {
//         CHECK(c == inner->GetMaterial().color);
//       }
//     }
//   }
// }

// /// ===========================================================================
// /// @section Shadows
// /// ===========================================================================

// SCENARIO("There is no shadow when nothing is collinear with point and light")
// {
//   GIVEN("w = default_world() && p = point(0, 10, 0)")
//   {
//     auto w = default_world();
//     auto p = make_point(0, 10, 0);

//     THEN("is_shadowed(w, p) is false") { CHECK(is_shadowed(w, p) == false); }
//   }
// }

// SCENARIO("The shadow when an object is between the point and the light")
// {
//   GIVEN("w = default_world() && p = point(10, -10, 10)")
//   {
//     auto w = default_world();
//     auto p = make_point(10, -10, 10);

//     THEN("is_shadowed(w, p) is true") { CHECK(is_shadowed(w, p) == true); }
//   }
// }

// SCENARIO("There is no shadow when an object is behind the light")
// {
//   GIVEN("w = default_world() && p = point(-20, 20, -20)")
//   {
//     auto w = default_world();
//     auto p = make_point(-20, 20, -20);

//     THEN("is_shadowed(w, p) is false") { CHECK(is_shadowed(w, p) == false); }
//   }
// }

// SCENARIO("There is no shadow when an object is behind the point")
// {
//   GIVEN("w = default_world() && p = point(-2, 2, -2)")
//   {
//     auto w = default_world();
//     auto p = make_point(-2, 2, -2);

//     THEN("is_shadowed(w, p) is false") { CHECK(is_shadowed(w, p) == false); }
//   }
// }

// SCENARIO("shade_hit() is given an intersection in shadow")
// {
//   GIVEN("w = world() &&\
//   \n w.light = point_light(point(0, 0, -10), color(1, 1, 1)) &&\
//   \n s1 = sphere() && s1 is added to w &&\
//   \n s2 = sphere() with:\
//   \n | transform | translation(0, 0, 10) |\
//   \n AND s2 is added to w &&\
//   \n r = ray(point(0, 0, 5), vector(0, 0, 1)) &&\
//   \n i = intersection(4, s2)")
//   {
//     auto w = World();
//     w.SetLight(PointLight{ make_point(0, 0, -10), make_color(1, 1, 1) });

//     auto s1 = std::make_shared<Sphere>();
//     w.AddObject(std::static_pointer_cast<Shape>(s1));

//     auto s2 = std::make_shared<Sphere>();
//     s2->SetTransform(translation(0, 0, 10));
//     w.AddObject(std::static_pointer_cast<Shape>(s2));

//     auto r = Ray{ make_point(0, 0, 0), make_vector(0, 0, 1) };
//     auto i = Intersection(4, s2.get());

//     WHEN("comps = prepare_computations(i, r) &&\
//     \n c = shade_hit(w, comps)")
//     {
//       auto comps = prepare_computations(i, r);
//       auto c = shade_hit(w, comps);

//       THEN("c == color(0.1, 0.1, 0.1)")
//       {
//         CHECK(c == make_color(0.1, 0.1, 0.1));
//       }
//     }
//   }
// }

// /// ===========================================================================
// /// @section Reflection
// /// ===========================================================================

// SCENARIO("The reflected color for a nonreflective material")
// {
//   GIVEN("w = default_world() &&\
//   \n r = ray(point(0, 0, 0,), vector(0, 0, 1)) &&\
//   \n shape = second object in w &&\
//   \n shape.material.ambient = 1 &&\
//   \n i = intersection(1, shape)")
//   {
//     auto w = default_world();
//     auto r = Ray{ make_point(0, 0, 0), make_vector(0, 0, 1) };
//     auto& shape = w.GetObjects()[1];
//     shape->SetMaterial().ambient = 1;
//     auto i = Intersection(1, shape.get());

//     WHEN("comps = prepare_computations(i, r) &&\
//     \n color = reflected_color(w, comps)")
//     {
//       auto comps = prepare_computations(i, r);
//       auto color = reflected_color(w, comps);

//       THEN("color == color(0, 0, 0,)") { CHECK(color == make_color(0, 0, 0)); }
//     }
//   }
// }

// SCENARIO("shade_hit() for a reflective material")
// {
//   GIVEN("w = default_world() &&\
//   \n shape = plane() with:\
//     \n | material.reflective | 0.5                   |\
//     \n | transform           | translation(0, -1, 0) |\
//     \n AND shape is added to w &&\
//     \n r = ray(point(0, 0, -3), vector(0, -SQRT(2)/2, SQRT(2)/2)) &&\
//     \n i = intersection(SQRT(2), shape)")
//   {
//     auto w = default_world();
//     auto shape = std::make_shared<Plane>();
//     shape->SetMaterial().reflective = 0.5;
//     shape->SetTransform(translation(0, -1, 0));
//     w.AddObject(shape);
//     auto sqrt2 = std::sqrt(2);
//     auto r = Ray{ make_point(0, 0, -3), make_vector(0, -sqrt2 / 2, sqrt2 / 2) };
//     auto i = Intersection(sqrt2, shape.get());

//     WHEN("comps = prepare_computations(i, r) &&\
//     \n color = shade_hit(w, comps)")
//     {
//       auto comps = prepare_computations(i, r);
//       auto color = shade_hit(w, comps);

//       THEN("color == color(0.87677, 0.92436, 0.82918)")
//       {
//         CHECK(color == make_color(0.87677, 0.92436, 0.82918));
//       }
//     }
//   }
// }

// SCENARIO("color_at() with mutually reflective surfaces")
// {
//   GIVEN("w = world() &&\
//   \n w.light = point_light(point(0, 0, 0), color(1, 1, 1)) &&\
//   \n lower = plane() with:\
//     \n | material.reflective | 1                     |\
//     \n | transform           | translation(0, -1, 0) |\
//     \n AND lower is added to w &&\
//     \n upper = plane() with:\
//     \n | material.reflective | 1                    |\
//     \n | transform           | translation(0, 1, 0) |\
//     \n AND upper is added to w &&\
//     \n r = ray(point(0, 0, 0,), vector(0, 1, 0))")
//   {
//     auto w = World();

//     w.SetLight(PointLight(make_point(0, 0, 0), make_vector(1, 1, 1)));

//     auto lower = std::make_shared<Plane>();
//     lower->SetMaterial().reflective = 1;
//     lower->SetTransform(translation(0, -1, 0));
//     w.AddObject(lower);

//     auto upper = std::make_shared<Plane>();
//     upper->SetMaterial().reflective = 1;
//     upper->SetTransform(translation(0, 1, 0));
//     w.AddObject(upper);

//     auto r = Ray{ make_point(0, 0, 0), make_vector(0, 1, 0) };

//     THEN("color_at(w, r) should terminate successfully")
//     {
//       CHECK_NOTHROW(color_at(w, r));
//     }
//   }
// }

// SCENARIO("The reflected color at the maximum recursive depth")
// {
//   GIVEN("w = default_world() &&\
//   \n shape = plane() with:\
//     \n | material.reflective | 0.5                   |\
//     \n | transform           | translation(0, -1, 0) |\
//     \n AND shape is added to w &&\
//     \n r = ray(point(0, 0, -3), vector(0, -SQRT(2)/2, SQRT(2)/2)) &&\
//     \n i = intersection(SQRT(2), shape)")
//   {
//     auto w = default_world();
//     auto shape = std::make_shared<Plane>();
//     shape->SetMaterial().reflective = 0.5;
//     shape->SetTransform(translation(0, -1, 0));
//     w.AddObject(shape);
//     auto sqrt2 = std::sqrt(2);
//     auto r = Ray{ make_point(0, 0, -3), make_vector(0, -sqrt2 / 2, sqrt2 / 2) };
//     auto i = Intersection(sqrt2, shape.get());

//     WHEN("comps = prepare_computations(i, r) &&\
//     \n color = reflected_color(w, comps, 0)")
//     {
//       auto comps = prepare_computations(i, r);
//       auto color = reflected_color(w, comps, 0);

//       THEN("color == color(0, 0, 0)") { CHECK(color == make_color(0, 0, 0)); }
//     }
//   }
// }

// /// ===========================================================================
// /// @section Refraction
// /// ===========================================================================

// SCENARIO("The refracted color with an opaque surface")
// {
//   GIVEN("w = default_world() &&\
//   \n shape = the first object in w &&\
//   \n r = ray(point(0, 0, -5), vector(0, 0, 1)) &&\
//   \n xs = intersections(4:shape, 6:shape)")
//   {
//     const auto w = default_world();
//     const auto& shape = w.GetObjects().front();
//     const auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };
//     const Intersections xs{ { 4, shape.get() }, { 6, shape.get() } };

//     WHEN("comps = prepare_computations(xs[0], r, xs) &&\
//     \n c = refracted_color(w, comps, 5)")
//     {
//       auto comps = prepare_computations(xs[0], r, &xs);
//       auto c = refracted_color(w, comps, 5);

//       THEN("c == color(0, 0, 0)") { CHECK(c == make_color(0, 0, 0)); }
//     }
//   }
// }

// SCENARIO("The refracted color at the maximum recursive depth")
// {
//   GIVEN("w = default_world() &&\
//   \n shape = the first object in w &&\
//   \n shape has:\
//   \n | material.transparency     | 1.0 |\
//   \n | material.refractive_index | 1.5 |\
//   \n AND r = ray(point(0, 0, -5), vector(0, 0, 1)) &&\
//   \n xs = intersections(4:shape, 6:shape)")
//   {
//     const auto w = default_world();
//     const auto shape = w.GetObjects().front();
//     shape->SetMaterial().transparency = 1.0;
//     shape->SetMaterial().refractiveIndex = 1.5;
//     const auto r = Ray{ make_point(0, 0, -5), make_vector(0, 0, 1) };
//     const auto xs = Intersections{ { 4, shape.get() }, { 6, shape.get() } };

//     WHEN("comps = prepare_computations(xs[0], r, xs) &&\
//     \n c = refracted_color(w, comps, 0)")
//     {
//       auto comps = prepare_computations(xs[0], r, &xs);
//       auto c = refracted_color(w, comps, 0);

//       THEN("c == color(0, 0, 0)") { CHECK(c == make_color(0, 0, 0)); }
//     }
//   }
// }

// SCENARIO("The refracted color under total internal reflection")
// {
//   GIVEN("w = default_world() &&\
//   \n shape = the first object in w &&\
//   \n shape has:\
//   \n | material.transparency     | 1.0 |\
//   \n | material.refractive_index | 1.5 |\
//   \n AND r = ray(point(0, 0, SQRT(2)/2), vector(0, 1, 0)) &&\
//   \n AND xs = intersections(-SQRT(2)/2:shape, SQRT(2)/2:shape)")
//   {
//     const auto w = default_world();
//     const auto shape = w.GetObjects().front();
//     shape->SetMaterial().transparency = 1.0;
//     shape->SetMaterial().refractiveIndex = 1.5;
//     const auto sqrt2 = static_cast<float>(std::sqrt(2));
//     const auto r = Ray{ make_point(0, 0, sqrt2 / 2), make_vector(0, 1, 0) };
//     const auto xs =
//       Intersections{ { -sqrt2 / 2, shape.get() }, { sqrt2 / 2, shape.get() } };

//     WHEN("comps = prepare_computations(xs[1], r, xs) &&\
//     \n c = refracted_color(w, comps, 5)")
//     {
//       auto comps = prepare_computations(xs[1], r, &xs);
//       auto c = refracted_color(w, comps, 5);

//       THEN("c == color(0, 0, 0)") { CHECK(c == make_color(0, 0, 0)); }
//     }
//   }
// }

// /// ---------------------------------------------------------------------------
// class TestPattern : public Pattern
// {
// public:
//   ~TestPattern() override = default;
//   TestPattern() = default;

//   Color At(Tuple point) const override
//   {
//     return make_color(point.x, point.y, point.z);
//   }
// };
// /// ---------------------------------------------------------------------------

// SCENARIO("The refracted color with a refracted ray")
// {
//   GIVEN("w = default_world()\
//   \n\t And A = the first object in w\
//   \n\t And A has:\
//   \n\t  | material.ambient | 1.0            |\
//   \n\t  | material.pattern | test_pattern() |\
//   \n\t And B = the second object in w\
//   \n\t And B has:\
//   \n\t  | material.transparency     | 1.0 |\
//   \n\t  | material.refractive_index | 1.5 |\
//   \n\t And r = ray(point(0, 0, 0.1), vector(0, 1, 0))\
//   \n\t And xs = intersections(-0.9899:A, -0.4899:B, 0.4899:B, 0.9899:A)")
//   {
//     const auto w = default_world();
//     Shape* A = w.GetObjects()[0].get();
//     A->SetMaterial().ambient = 1.0;
//     A->SetMaterial().pattern = std::make_shared<TestPattern>();
//     Shape* B = w.GetObjects()[1].get();
//     B->SetMaterial().transparency = 1.0;
//     B->SetMaterial().refractiveIndex = 1.5;
//     const auto r = Ray{ make_point(0, 0, 0.1), make_vector(0, 1, 0) };
//     const auto xs = Intersections{
//       { -0.9899, A }, { -0.4899, B }, { 0.4899, B }, { 0.9899, A }
//     };

//     WHEN("comps = prepare_computations(xs[2], r, xs) &&\
//     \n\t And c = refracted_color(w, comps, 5)")
//     {
//       auto comps = prepare_computations(xs[2], r, &xs);
//       auto c = refracted_color(w, comps, 5);

//       THEN("c == color(0, 0.99888, 0.04725)")
//       {
//         CHECK(c == make_color(0, 0.99888, 0.04725));
//       }
//     }
//   }
// }

// SCENARIO("shade_hit() with a transparent material")
// {
//   GIVEN("w = default_world()\
//   \n\t And floor = plane() with:\
//   \n\t  | transform                 | translation(0, -1, 0) |\
//   \n\t  | material.transparency     | 0.5                   |\
//   \n\t  | material.refractive_index | 1.5                   |\
//   \n\t And floor is added to w\
//   \n\t And ball = sphere() with:\
//   \n\t  | material.color     | (1, 0, 0)                  |\
//   \n\t  | material.ambient   | 0.5                        |\
//   \n\t  | transform          | translation(0, -3.5, -0.5) |\
//   \n\t And ball is added to w\
//   \n\t And r = ray(point(0, 0, -3), vector(0, -SQRT(2)/2), SQRT(2)/2))\
//   \n\t And xs = intersections(SQRT(2):floor)")
//   {
//     auto w = default_world();
//     auto floor = std::make_shared<Plane>();
//     floor->SetTransform(translation(0, -1, 0));
//     floor->SetMaterial().transparency = 0.5;
//     floor->SetMaterial().refractiveIndex = 1.5;
//     w.AddObject(floor);
//     auto ball = std::make_shared<Sphere>();
//     ball->SetMaterial().color = make_color(1, 0, 0);
//     ball->SetMaterial().ambient = 0.5;
//     w.AddObject(ball);
//     float sqrt2 = std::sqrt(2);
//     auto r = Ray{ make_point(0, 0, -3), make_vector(0, -sqrt2 / 2, sqrt2 / 2) };
//     auto xs = Intersections{ { sqrt2, floor.get() } };

//     WHEN("comps = prepare_computations(xs[0], r, xs)\
//     \n\t And color = shade_hit(w, comps, 5)")
//     {
//       auto comps = prepare_computations(xs[0], r, &xs);
//       auto c = shade_hit(w, comps, 5);
//       THEN("c == color(0.93642, 0.68642, 0.68642)")
//       {
//         CHECK(c == make_color(0.93642, 0.68642, 0.68642));
//       }
//     }
//   }
// }

// SCENARIO("shade_hit() with a reflective, transparent material")
// {
//   GIVEN("given w = default_world()\
//   \n\t And r = ray(point(0, 0, -3), vector(0, -SQRT(2)/2, SQRT(2)/2))\
//   \n\t And floor = plane() with:\
//   \n\t  | transform                 | translation(0, -1, 0) |\
//   \n\t  | material.reflective       | 0.5                   |\
//   \n\t  | material.transparency     | 0.5                   |\
//   \n\t  | material.refractive_index | 1.5                   |\
//   \n\t And floor is added to w\
//   \n\t And ball = sphere() with:\
//   \n\t  | material.color    | (1, 0, 0)                  |\
//   \n\t  | material.ambient  | 0.5                        |\
//   \n\t  | transform         | translation(0, -3.5, -0.5) |\
//   \n\t And ball is added to w\
//   \n\t And xs = intersections(SQRT(2):floor)")
//   {
//     auto w = default_world();
//     auto sqrt2 = static_cast<float>(std::sqrt(2));
//     auto r = Ray{ make_point(0, 0, -3), make_vector(0, -sqrt2 / 2, sqrt2 / 2) };
//     auto floor = std::make_shared<Plane>();
//     floor->SetTransform(translation(0, -1, 0));
//     floor->SetMaterial().reflective = 0.5;
//     floor->SetMaterial().transparency = 0.5;
//     floor->SetMaterial().refractiveIndex = 1.5;
//     w.AddObject(floor);
//     auto ball = std::make_shared<Sphere>();
//     ball->SetMaterial().color = make_color(1, 0, 0);
//     ball->SetMaterial().ambient = 0.5;
//     ball->SetTransform(translation(0, -3.5, -0.5));
//     w.AddObject(ball);
//     auto xs = Intersections{ { sqrt2, floor.get() } };

//     WHEN("comps = prepare_computations(xs[0], r, xs)\
//     \n\t And c = shade_hit(w, comps, 5)")
//     {
//       auto comps = prepare_computations(xs[0], r, &xs);
//       auto c = shade_hit(w, comps, 5);

//       THEN("c == color(0.93391, 0.69643, 0.69243)")
//       {
//         CHECK(c == make_color(0.93391, 0.69643, 0.69243));
//       }
//     }
//   }
// }
