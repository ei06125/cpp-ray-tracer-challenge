#pragma once
#include "RayTracerPCH.hpp"

// Project Library
#include "RayTracer/Math/Constants.hpp"

namespace RayTracer::Math {

struct Tuple
{
  Tuple(float x_, float y_, float z_, float w_);
  float x;
  float y;
  float z;
  float w;
};

/// @section Non-member functions

/// @subsection Creation Methods

Tuple Point(float x, float y, float z);
Tuple Vector(float x, float y, float z);

bool isPoint(Tuple aTuple);  // Useless API (only used in tests)
bool isVector(Tuple aTuple); // Useless API (only used in tests)

/// @subsection Arithmetic operators

std::ostream& operator<<(std::ostream& os, const Tuple& aTuple);

Tuple operator+(const Tuple& lhs, const Tuple& rhs);

Tuple operator-(const Tuple& lhs, const Tuple& rhs);

Tuple operator-(const Tuple& rhs); // Negate

Tuple operator*(const Tuple& lhs, float s);

Tuple operator*(float s, const Tuple& rhs);

Tuple operator*(const Tuple& lhs, const Tuple& rhs); // Hadamard product

Tuple operator/(const Tuple& lhs, float s);

/// @subsection Logic operators

bool operator==(const Tuple& lhs, const Tuple& rhs);

/// @subsection Vector API

float magnitude(Tuple aTuple);

Tuple normalize(Tuple v);

float dot(const Tuple& a, const Tuple& b);

Tuple cross(const Tuple& a, const Tuple& b);

Tuple reflect(const Tuple& aVector, const Tuple& aNormal);

} // namespace RayTracer::Math
