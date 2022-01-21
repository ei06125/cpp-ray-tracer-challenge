#pragma once

// C++ Standard Library
#include <iosfwd>

// Project Library
#include "Math/Constants.hpp"

struct Tuple
{
  Tuple(float x_, float y_, float z_, float w_);
  union
  {
    float x;
    float red;
  };
  union
  {
    float y;
    float green;
  };
  union
  {
    float z;
    float blue;
  };
  union
  {
    float w;
    float alpha;
  };
};

Tuple make_point(float x, float y, float z);

Tuple make_vector(float x, float y, float z);

Tuple make_color(float r, float g, float b);

bool isPoint(Tuple aTuple);

bool isVector(Tuple aTuple);

std::ostream& operator<<(std::ostream& os, const Tuple& aTuple);

bool operator==(const Tuple& lhs, const Tuple& rhs);

Tuple operator+(const Tuple& lhs, const Tuple& rhs);

Tuple operator-(const Tuple& lhs, const Tuple& rhs);

Tuple operator-(const Tuple& rhs); // Negate

Tuple operator*(const Tuple& lhs, float s);

Tuple operator*(float s, const Tuple& rhs);

Tuple operator*(const Tuple& lhs, const Tuple& rhs); // Hadamard product

Tuple operator/(const Tuple& lhs, float s);

float magnitude(Tuple aTuple);

Tuple normalize(Tuple v);

float dot(const Tuple& a, const Tuple& b);

Tuple cross(const Tuple& a, const Tuple& b);

Tuple reflect(const Tuple& aVector, const Tuple& aNormal);
