#ifndef TUPLES_HPP
#define TUPLES_HPP

#include <iosfwd>

constexpr float EPSILON{0.0001f};

struct Tuple {
  Tuple(float x_, float y_, float z_, float w_);
  float x, y, z, w;
};

Tuple make_point(float x, float y, float z);

Tuple make_vector(float x, float y, float z);

bool isPoint(Tuple aTuple);

bool isVector(Tuple aTuple);

std::ostream &operator<<(std::ostream &os, const Tuple &aTuple);

bool operator==(const Tuple &lhs, const Tuple &rhs);

Tuple operator+(const Tuple &lhs, const Tuple &rhs);

Tuple operator-(const Tuple &lhs, const Tuple &rhs);

Tuple operator-(const Tuple &rhs); // Negate

Tuple operator*(const Tuple &lhs, float s);

Tuple operator*(float s, const Tuple &rhs);

Tuple operator/(const Tuple &lhs, float s);

float magnitude(Tuple aTuple);

Tuple normalize(Tuple v);

float dot(const Tuple &a, const Tuple &b);

Tuple cross(const Tuple &a, const Tuple &b);

#endif // TUPLES_HPP
