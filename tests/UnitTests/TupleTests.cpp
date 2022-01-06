// Test Framework
#include "doctest/doctest.h"

// C Standard Library
#include <cmath>

// C++ Standard Library
#include <iostream>

// Project Library
#include "Tuple.hpp"


// ============================================================================

SCENARIO("A tuple with w = 1 is a point") {
  GIVEN("a = Tuple(4.3, -4.2, 3.1, 1.0") {
    auto a = Tuple(4.3f, -4.2f, 3.1f, 1.0f);
    THEN("a.x == 4.3\
    AND a.y == -4.2\
    AND a.z == 3.1\
    AND a.w == 1.0\
    AND a is a point\
    AND a is not a vector") {
      CHECK(a.x == 4.3f);
      CHECK(a.y == -4.2f);
      CHECK(a.z == 3.1f);
      CHECK(a.w == 1.0f);
      CHECK(isPoint(a));
      CHECK(!isVector(a));
    }
  }
}

SCENARIO("A tuple with w = 0 is a vector") {
  GIVEN("a = Tuple(4.3, -4.2, 3.1, 1.0") {
    auto a = Tuple(4.3f, -4.2f, 3.1f, 0.0f);
    THEN("a.x == 4.3\
    AND a.y == -4.2\
    AND a.z == 3.1\
    AND a.w == 0.0\
    AND a is a vector\
    AND a is not a point") {
      CHECK(a.x == 4.3f);
      CHECK(a.y == -4.2f);
      CHECK(a.z == 3.1f);
      CHECK(a.w == 0.0f);
      CHECK(!isPoint(a));
      CHECK(isVector(a));
    }
  }
}

SCENARIO("point() creates tuples with w=1") {
  GIVEN("p = point(4, -4, 3)") {
    auto p = make_point(4, -4, 3);
    THEN("p == tuple(4, -4, 3, 1)") { CHECK(p == Tuple(4, -4, 3, 1)); }
  }
}

SCENARIO("vector() creates tuples with w=0") {
  GIVEN("p = point(4, -4, 3)") {
    auto p = make_vector(4, -4, 3);
    THEN("p == tuple(4, -4, 3, 0)") { CHECK(p == Tuple(4, -4, 3, 0)); }
  }
}

SCENARIO("Adding two tuples") {
  GIVEN("a1 = tuple(3, -2, 5, 1) AND a2 = tuple(-2,3,1,0)") {
    auto a1 = Tuple(3, -2, 5, 1);
    auto a2 = Tuple(-2, 3, 1, 0);
    THEN("a1 + a2 == tuple(1, 1, 6, 1)") {
      CHECK(a1 + a2 == Tuple(1, 1, 6, 1));
    }
  }
}

SCENARIO("Subtracting two points") {
  GIVEN("p1 = point(3, 2, 1) AND p2 = point(5, 6, 7)") {
    auto p1 = make_point(3, 2, 1);
    auto p2 = make_point(5, 6, 7);
    THEN("p1 - p2 == vector(-2, -4, -6") {
      CHECK(p1 - p2 == make_vector(-2, -4, -6));
    }
  }
}

SCENARIO("Subtracting a vector from a point") {
  GIVEN("p = point(3, 2, 1) AND v = vector(5, 6, 7)") {
    auto p = make_point(3, 2, 1);
    auto v = make_vector(5, 6, 7);
    THEN("p - v == point(-2, -4, -6") {
      CHECK(p - v == make_point(-2, -4, -6));
    }
  }
}

SCENARIO("Subtracting two vectors") {
  GIVEN("v1 = vector(3, 2, 1) AND v2 = vector(5, 6, 7)") {
    auto v1 = make_vector(3, 2, 1);
    auto v2 = make_vector(5, 6, 7);
    THEN("v1 - v2 == vector(-2, -4, -6") {
      CHECK(v1 - v2 == make_vector(-2, -4, -6));
    }
  }
}

SCENARIO("Subtracting a vector from the zero vector") {
  GIVEN("zero = vector(0, 0, 0) AND v = vector(1, -2, 3)") {
    auto zero = make_vector(0, 0, 0);
    auto v = make_vector(1, -2, 3);
    THEN("zero - v == vector(-1, 2, -3)") {
      CHECK(zero - v == make_vector(-1, 2, -3));
    }
  }
}

SCENARIO("Negating a tuple") {
  GIVEN("a = tuple(1, -2, 3, -4)") {
    auto a = Tuple(1, -2, 3, -4);
    THEN("-a == tuple(-1, 2, -3, 4)") { CHECK(-a == Tuple(-1, 2, -3, 4)); }
  }
}

SCENARIO("Multiplying a tuple by a scalar") {
  GIVEN("a = tuple(1, -2, 3, -4)") {
    auto a = Tuple(1, -2, 3, -4);
    THEN("a * 3.5 == tuple(3.5, -7, 10.5, -14)") {
      CHECK(a * 3.5 == Tuple(3.5, -7, 10.5, -14));
    }
  }
}

SCENARIO("Multiplying a tuple by a fraction") {
  GIVEN("a = tuple(1, -2, 3, -4)") {
    auto a = Tuple(1, -2, 3, -4);
    THEN("a * 0.5 == tuple(0.5, -1, 1.5, -2)") {
      CHECK(a * 0.5 == Tuple(0.5, -1, 1.5, -2));
    }
  }
}

SCENARIO("Dividing a tuple by a scalar") {
  GIVEN("a = tuple(1, -2, 3, -4)") {
    auto a = Tuple(1, -2, 3, -4);
    THEN("a / 2 == tuple(0.5, -1, 1.5, -2)") {
      CHECK(a / 2 == Tuple(0.5, -1, 1.5, -2));
    }
  }
}

SCENARIO("Computing the magnitude of vector(1, 0, 0)") {
  GIVEN("v = vector(1, 0, 0)") {
    auto v = make_vector(1, 0, 0);
    THEN("magnitude(v) == 1") { CHECK(magnitude(v) == 1); }
  }
}

SCENARIO("Computing the magnitude of vector(0, 1, 0)") {
  GIVEN("v = vector(0, 1, 0)") {
    auto v = make_vector(0, 1, 0);
    THEN("magnitude(v) == 1") { CHECK(magnitude(v) == 1); }
  }
}

SCENARIO("Computing the magnitude of vector(0, 0, 1)") {
  GIVEN("v = vector(0, 0, 1)") {
    auto v = make_vector(0, 0, 1);
    THEN("magnitude(v) == 1") { CHECK(magnitude(v) == 1); }
  }
}

SCENARIO("Computing the magnitude of vector(1, 2, 3)") {
  GIVEN("v = vector(1, 2, 3)") {
    auto v = make_vector(1, 2, 3);
    THEN("magnitude(v) == sqrt(14)") {
      CHECK(magnitude(v) == doctest::Approx(std::sqrt(14)));
    }
  }
}

SCENARIO("Computing the magnitude of vector(-1, -2, -3)") {
  GIVEN("v = vector(-1, -2, -3)") {
    auto v = make_vector(-1, -2, -3);
    THEN("magnitude(v) == sqrt(14)") {
      CHECK(magnitude(v) == doctest::Approx(std::sqrt(14)));
    }
  }
}

SCENARIO("Normalizing vector(4, 0, 0) gives (1, 0, 0)") {
  GIVEN("v = vector(4, 0, 0)") {
    auto v = make_vector(4, 0, 0);
    THEN("normalize(v) == vector(1, 0, 0)") {
      CHECK(normalize(v) == make_vector(1, 0, 0));
    }
  }
}

SCENARIO("Normalizing vector(1, 2, 3)") {
  GIVEN("v = vector(1, 2, 3)") {
    auto v = make_vector(1, 2, 3);
    THEN("normalize(v) == approximately vector(") {
      auto result = normalize(v);
      auto sqrt14 = std::sqrt(14);
      CHECK(result.x == doctest::Approx(1 / sqrt14));
      CHECK(result.y == doctest::Approx(2 / sqrt14));
      CHECK(result.z == doctest::Approx(3 / sqrt14));
    }
  }
}

SCENARIO("The magnitude of a  normalized vector") {
  GIVEN("v = vector(1, 2, 3)") {
    auto v = make_vector(1, 2, 3);
    WHEN("norm = normalize(v)") {
      auto norm = normalize(v);
      THEN("magnitude(norm) == 1") {
        CHECK(magnitude(norm) == doctest::Approx(1));
      }
    }
  }
}

SCENARIO("The dot product of two tuples") {
  GIVEN("a = vector(1, 2, 3) AND b = vector(2, 3, 4)") {
    auto a = make_vector(1, 2, 3);
    auto b = make_vector(2, 3, 4);
    THEN("dot(a, b) == 20") { CHECK(dot(a, b) == doctest::Approx(20)); }
  }
}

SCENARIO("The cross product of two tuples") {
  GIVEN("a = vector(1, 2, 3) AND b = vector(2, 3, 4)") {
    auto a = make_vector(1, 2, 3);
    auto b = make_vector(2, 3, 4);
    THEN("cross(a, b) == vector(-1, 2, -1)\
      AND cross(b, a) == vector(1, -2, 1)") {
      CHECK(cross(a, b) == make_vector(-1, 2, -1));
      CHECK(cross(b, a) == make_vector(1, -2, 1));
    }
  }
}