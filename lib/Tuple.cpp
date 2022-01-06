#include "Tuple.hpp"

// C++ Standard Library
#include <iostream>

// C Standard Library
#include <cmath>

Tuple::Tuple(float x_, float y_, float z_, float w_)
    : x(x_), y(y_), z(z_), w(w_) {}

Tuple make_point(float x, float y, float z) { return Tuple(x, y, z, 1.0f); }

Tuple make_vector(float x, float y, float z) { return Tuple(x, y, z, 0.0f); }

bool isPoint(Tuple aTuple) { return aTuple.w == 1.0f; }

bool isVector(Tuple aTuple) { return aTuple.w == 0.0f; }

std::ostream &operator<<(std::ostream &os, const Tuple &aTuple) {
  os << "{ x:" << aTuple.x << ", y:" << aTuple.y << ", z:" << aTuple.z
     << ", w:" << aTuple.w << " }";
  return os;
}

bool operator==(const Tuple &lhs, const Tuple &rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

Tuple operator+(const Tuple &lhs, const Tuple &rhs) {
  return Tuple(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

Tuple operator-(const Tuple &lhs, const Tuple &rhs) {
  return Tuple(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

Tuple operator-(const Tuple &rhs) {
  return Tuple(-rhs.x, -rhs.y, -rhs.z, -rhs.w);
}

Tuple operator*(const Tuple &lhs, float s) {
  return Tuple(lhs.x * s, lhs.y * s, lhs.z * s, lhs.w * s);
}

Tuple operator*(float s, const Tuple &rhs) { return rhs * s; }

Tuple operator/(const Tuple &lhs, float s) {
  return Tuple(lhs.x / s, lhs.y / s, lhs.z / s, lhs.w / s);
}

float magnitude(Tuple v) {
  return std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

Tuple normalize(Tuple v) {
  auto mag = magnitude(v);
  return Tuple(v.x / mag, v.y / mag, v.z / mag, v.w / mag);
}

float dot(const Tuple &a, const Tuple &b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

Tuple cross(const Tuple &a, const Tuple &b) {
  return make_vector(            //
      (a.y * b.z) - (a.z * b.y), //
      (a.z * b.x) - (a.x * b.z), //
      (a.x * b.y) - (a.y * b.x)  //
  );
}
