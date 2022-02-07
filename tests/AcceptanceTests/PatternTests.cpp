// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

using namespace RayTracer::Math;
using namespace RayTracer::Rendering;
using namespace RayTracer::Rendering::Patterns;
using namespace RayTracer::Rendering::Primitives;

/// ===========================================================================
/// @section Stubs
/// ===========================================================================

class TestPattern : public Pattern
{
public:
  /// @section Member functions
  ~TestPattern() override = default;
  TestPattern() = default;

  /// @subsection Observers
  Color At(Tuple point) const override
  {
    return Color{ point.x, point.y, point.z };
  }
};

/// ===========================================================================
/// @section Tests
/// ===========================================================================

SCENARIO("The default pattern transformation")
{
  GIVEN("pattern = test_pattern()")
  {
    auto pattern = TestPattern();

    THEN("pattern.transform == identity_matrix")
    {
      CHECK(pattern.GetTransform() == mat4::Identity());
    }
  }
}

SCENARIO("Assigning a transformation")
{
  GIVEN("pattern = test_pattern()")
  {
    auto pattern = TestPattern();

    WHEN("set_pattern_transform(pattern, translation(1, 2, 3))")
    {
      pattern.SetTransform(translation(1, 2, 3));
      THEN("pattern.transform == translation(1, 2 ,3)")
      {
        CHECK(pattern.GetTransform() == translation(1, 2, 3));
      }
    }
  }
}

SCENARIO("A pattern with an object transformation")
{
  GIVEN("shape = sphere() &&\
  \n set_transform(shape, scaling(2, 2, 2)) &&\
  \n pattern = test_pattern()")
  {
    auto shape = Sphere();
    shape.SetTransform(scaling(2, 2, 2));
    auto pattern = TestPattern();

    WHEN("c = stripe_at_shape(pattern, shape, point(2, 3, 4))")
    {
      auto c = pattern.AtShape(&shape, Point(2, 3, 4));

      THEN("c == color(1, 1.5, 2)") { CHECK(c == Color{ 1.0f, 1.5f, 2.0f }); }
    }
  }
}

SCENARIO("A pattern with a pattern transformation")
{
  GIVEN("shape = sphere() &&\
  \n pattern = test_pattern() &&\
  \n set_pattern_transform(pattern, scaling(2, 2, 2))")
  {
    auto shape = Sphere();
    auto pattern = TestPattern();
    pattern.SetTransform(scaling(2, 2, 2));

    WHEN("c = stripe_at_shape(pattern, shape, point(2, 3, 4))")
    {
      auto c = pattern.AtShape(&shape, Point(2, 3, 4));

      THEN("c == color(1, 1.5, 2)") { CHECK(c == Color{ 1.0f, 1.5f, 2.0f }); }
    }
  }
}

SCENARIO("A pattern with both an object and a pattern transformation")
{
  GIVEN("shape = sphere() &&\
  \n set_transform(shape, scaling(2, 2, 2)) &&\
  \n pattern = test_pattern() &&\
  \n set_pattern_transform(pattern, translation(0.5, 1, 1.5))")
  {
    auto shape = Sphere();
    shape.SetTransform(scaling(2, 2, 2));

    auto pattern = TestPattern();
    pattern.SetTransform(translation(0.5, 1, 1.5));

    WHEN("c = stripe_at_shape(pattern, shape, point(2.5, 3, 3.5))")
    {
      auto c = pattern.AtShape(&shape, Point(2.5, 3, 3.5));
      THEN("c == color(0.75, 0.5, 0.25)")
      {
        CHECK(c == Color{ 0.75f, 0.5f, 0.25f });
      }
    }
  }
}

/// ---------------------------------------------------------------------------
/// @subsection Solid Color Pattern
/// ---------------------------------------------------------------------------

/// ---------------------------------------------------------------------------
/// @subsection Stripe Pattern
/// ---------------------------------------------------------------------------

SCENARIO("Creating a stripe pattern")
{
  GIVEN("pattern = stripe_pattern(white, black)")
  {
    auto pattern = StripePattern{ Colors::White, Colors::Black };

    THEN("pattern.a == white && pattern.b == black")
    {
      CHECK(pattern.A() == Colors::White);
      CHECK(pattern.B() == Colors::Black);
    }
  }
}

SCENARIO("A stripe pattern is constant in y")
{
  GIVEN("pattern = stripe_pattern(white, black)")
  {
    auto pattern = StripePattern{ Colors::White, Colors::Black };

    THEN("stripe_at(pattern, point(0, 0, 0)) == white &&\
    \n stripe_at(pattern, point(0, 1, 0)) == white &&\
    \n stripe_at(pattern, point(0, 2, 0)) == white")
    {
      CHECK(pattern.At(Point(0, 0, 0)) == Colors::White);
      CHECK(pattern.At(Point(0, 1, 0)) == Colors::White);
      CHECK(pattern.At(Point(0, 2, 0)) == Colors::White);
    }
  }
}

SCENARIO("A stripe pattern is constant in z")
{
  GIVEN("pattern = stripe_pattern(white, black)")
  {
    auto pattern = StripePattern{ Colors::White, Colors::Black };

    THEN("stripe_at(pattern, point(0, 0, 0)) == white &&\
    \n stripe_at(pattern, point(0, 0, 1)) == white &&\
    \n stripe_at(pattern, point(0, 0, 2)) == white")
    {
      CHECK(pattern.At(Point(0, 0, 0)) == Colors::White);
      CHECK(pattern.At(Point(0, 0, 1)) == Colors::White);
      CHECK(pattern.At(Point(0, 0, 2)) == Colors::White);
    }
  }
}

SCENARIO("A stripe pattern alternates in x")
{
  GIVEN("pattern = stripe_pattern(white, black)")
  {
    auto pattern = StripePattern{ Colors::White, Colors::Black };

    THEN("stripe_at(pattern, point(0, 0, 0)) == white &&\
    \n stripe_at(pattern, point(0.9, 0, 0)) == white &&\
    \n stripe_at(pattern, point(1, 0, 0)) == black &&\
    \n stripe_at(pattern, point(-0.1, 0, 0)) == black &&\
    \n stripe_at(pattern, point(-1, 0, 0)) == black &&\
    \n stripe_at(pattern, point(-1.1, 0, 0)) == white")
    {
      CHECK(pattern.At(Point(0, 0, 0)) == Colors::White);
      CHECK(pattern.At(Point(0.9, 0, 0)) == Colors::White);
      CHECK(pattern.At(Point(1, 0, 0)) == Colors::Black);
      CHECK(pattern.At(Point(-0.1, 0, 0)) == Colors::Black);
      CHECK(pattern.At(Point(-1, 0, 0)) == Colors::Black);
      CHECK(pattern.At(Point(-1.1, 0, 0)) == Colors::White);
    }
  }
}

/// ---------------------------------------------------------------------------
/// @subsection Gradient Pattern
/// ---------------------------------------------------------------------------

SCENARIO("A gradient linearly interpolates between colors")
{
  GIVEN("pattern = gradient_pattern(white, black)")
  {
    auto pattern = GradientPattern(Colors::White, Colors::Black);

    THEN("pattern_at(pattern, point(0, 0, 0)) == white &&\
    \n pattern_at(pattern, point(0.25, 0, 0)) == color(0.75, 0.75, 0.75) &&\
    \n pattern_at(pattern, point(0.5, 0, 0)) == color(0.5, 0.5, 0.5) &&\
    \n pattern_at(pattern, point(0.75, 0, 0)) == color(0.25, 0.25, 0.25)")
    {
      CHECK(pattern.At(Point(0, 0, 0)) == Colors::White);
      CHECK(pattern.At(Point(0.25, 0, 0)) == Color{ 0.75f, 0.75f, 0.75f });
      CHECK(pattern.At(Point(0.5, 0, 0)) == Color{ 0.5f, 0.5f, 0.5f });
      CHECK(pattern.At(Point(0.75, 0, 0)) == Color{ 0.25f, 0.25f, 0.25f });
    }
  }
}

/// ---------------------------------------------------------------------------
/// @subsection Ring Pattern
/// ---------------------------------------------------------------------------

SCENARIO("A ring should extend in both x and z")
{
  GIVEN("pattern = ring_pattern(white, black)")
  {
    auto pattern = RingPattern(Colors::White, Colors::Black);

    THEN("pattern_at(pattern, point(0, 0, 0)) == white &&\
    \n pattern_at(pattern, point(1, 0, 0)) == black &&\
    \n pattern_at(pattern, point(0, 0, 1)) == black &&\
    \n pattern_at(pattern, point(0.708, 0, 0.708)) == black")
    {
      CHECK(pattern.At(Point(0, 0, 0)) == Colors::White);
      CHECK(pattern.At(Point(1, 0, 0)) == Colors::Black);
      CHECK(pattern.At(Point(0, 0, 1)) == Colors::Black);
      // 0.708 = just slightly more than SQRT(2) / 2
      CHECK(pattern.At(Point(0.708, 0, 0.708)) == Colors::Black);
    }
  }
}

/// ---------------------------------------------------------------------------
/// @subsection 3D Checker Pattern
/// ---------------------------------------------------------------------------

SCENARIO("Checkers should repeat in x")
{
  GIVEN("pattern = checkers_pattern(white, black)")
  {
    auto pattern = CheckersPattern(Colors::White, Colors::Black);

    THEN("pattern_at(pattern, point(0, 0, 0)) == white &&\
    \n pattern_at(pattern, point(0.99, 0, 0)) == white &&\
    \n pattern_at(pattern, point(1.01, 0, 0)) == black))")
    {
      CHECK(pattern.At(Point(0, 0, 0)) == Colors::White);
      CHECK(pattern.At(Point(0.99, 0, 0)) == Colors::White);
      CHECK(pattern.At(Point(1.01, 0, 0)) == Colors::Black);
    }
  }
}

SCENARIO("Checkers should repeat in y")
{
  GIVEN("pattern = checkers_pattern(white, black)")
  {
    auto pattern = CheckersPattern(Colors::White, Colors::Black);

    THEN("pattern_at(pattern, point(0, 0, 0)) == white &&\
    \n pattern_at(pattern, point(0, 0.99, 0)) == white &&\
    \n pattern_at(pattern, point(0, 1.01, 0)) == black))")
    {
      CHECK(pattern.At(Point(0, 0, 0)) == Colors::White);
      CHECK(pattern.At(Point(0, 0.99, 0)) == Colors::White);
      CHECK(pattern.At(Point(0, 1.01, 0)) == Colors::Black);
    }
  }
}

SCENARIO("Checkers should repeat in z")
{
  GIVEN("pattern = checkers_pattern(white, black)")
  {
    auto pattern = CheckersPattern(Colors::White, Colors::Black);

    THEN("pattern_at(pattern, point(0, 0, 0)) == white &&\
    \n pattern_at(pattern, point(0, 0, 0.99)) == white &&\
    \n pattern_at(pattern, point(0, 0, 1.01)) == black))")
    {
      CHECK(pattern.At(Point(0, 0, 0)) == Colors::White);
      CHECK(pattern.At(Point(0, 0, 0.99)) == Colors::White);
      CHECK(pattern.At(Point(0, 0, 1.01)) == Colors::Black);
    }
  }
}

/// ---------------------------------------------------------------------------
/// @subsection Radial Gradient Pattern
/// ---------------------------------------------------------------------------

/// ---------------------------------------------------------------------------
/// @subsection Blended Pattern
/// ---------------------------------------------------------------------------

/// ---------------------------------------------------------------------------
/// @subsection Nested Pattern
/// ---------------------------------------------------------------------------

/// ---------------------------------------------------------------------------
/// @subsection Perturbed Pattern
/// ---------------------------------------------------------------------------
