// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

using namespace RayTracer::Rendering::Colors;

SCENARIO("Colors are (red, green, blue) tuples")
{
  GIVEN("c = color(-0.5, 0.4, 1.7)")
  {
    auto c = Color{ -0.5f, 0.4f, 1.7f };
    THEN("c.red == -0.5 && c.green == 0.4 && c.blue == 1.7")
    {
      CHECK(c.r == -0.5f);
      CHECK(c.g == 0.4f);
      CHECK(c.b == 1.7f);
    }
  }
}

SCENARIO("Adding colors")
{
  GIVEN("c1 = color(0.9, 0.6, 0.75) && c2 = color(0.7, 0.1, 0.25)")
  {
    auto c1 = Color{ 0.9f, 0.6f, 0.75f };
    auto c2 = Color{ 0.7f, 0.1f, 0.25f };
    THEN("c1 + c2 == color(1.6, 0.7, 1.0)")
    {
      CHECK(c1 + c2 == Color{ 1.6f, 0.7f, 1.0f });
    }
  }
}

SCENARIO("Subtracting colors")
{
  GIVEN("c1 = color(0.9, 0.6, 0.75) && c2 = color(0.7, 0.1, 0.25)")
  {
    auto c1 = Color{ 0.9f, 0.6f, 0.75f };
    auto c2 = Color{ 0.7f, 0.1f, 0.25f };
    THEN("c1 - c2 == color(0.2, 0.5, 0.5)")
    {
      CHECK(c1 - c2 == Color{ 0.2f, 0.5f, 0.5f });
    }
  }
}

SCENARIO("Multiplying a color by a scalar")
{
  GIVEN("c = color(0.2, 0.3, 0.4)")
  {
    auto c = Color{ 0.2f, 0.3f, 0.4f };
    THEN("c * 2 == color(0.4, 0.6, 0.8)")
    {
      CHECK(c * 2 == Color{ 0.4f, 0.6f, 0.8f });
    }
  }
}

SCENARIO("Multiplying colors")
{
  GIVEN("c1 = color(1, 0.2, 0.4) && c2 = color(0.9, 1, 0.1)")
  {
    auto c1 = Color{ 1.0f, 0.2f, 0.4f };
    auto c2 = Color{ 0.9f, 1.0f, 0.1f };
    THEN("c1 * c2 == color(0.9, 0.2, 0.04)")
    {
      CHECK(c1 * c2 == Color{ 0.9f, 0.2f, 0.04f });
    }
  }
}
