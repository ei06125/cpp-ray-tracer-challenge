#include "RayTracer/Math/Tuple.hpp"

#include "RayTracer/Math/Constants.hpp"

namespace RayTracer::Math {

using namespace Constants;

Tuple::Tuple(float x_, float y_, float z_, float w_)
  : x(x_)
  , y(y_)
  , z(z_)
  , w(w_)
{}

/// ===========================================================================
/// @section Non-member functions
/// ===========================================================================

Tuple Point(float x, float y, float z)
{
  return Tuple(x, y, z, 1.0f);
}

Tuple Vector(float x, float y, float z)
{
  return Tuple(x, y, z, 0.0f);
}

bool isPoint(Tuple aTuple)
{
  return aTuple.w == 1.0f;
}

bool isVector(Tuple aTuple)
{
  return aTuple.w == 0.0f;
}

/// ---------------------------------------------------------------------------
/// @subsection Arithmetic operators
/// ---------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const Tuple& aTuple)
{
  os << "{ x:" << std::fixed << std::setprecision(7) << aTuple.x
     << ", y:" << aTuple.y << ", z:" << aTuple.z << ", w:" << aTuple.w << " }";
  return os;
}

Tuple operator+(const Tuple& lhs, const Tuple& rhs)
{
  return Tuple(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

Tuple operator-(const Tuple& lhs, const Tuple& rhs)
{
  return Tuple(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

Tuple operator-(const Tuple& rhs)
{
  return Tuple(-rhs.x, -rhs.y, -rhs.z, -rhs.w);
}

Tuple operator*(const Tuple& lhs, float s)
{
  return Tuple(lhs.x * s, lhs.y * s, lhs.z * s, lhs.w * s);
}

Tuple operator*(float s, const Tuple& rhs)
{
  return rhs * s;
}

Tuple operator/(const Tuple& lhs, float s)
{
  return Tuple(lhs.x / s, lhs.y / s, lhs.z / s, lhs.w / s);
}

/// ---------------------------------------------------------------------------
/// @subsection Logic operators
/// ---------------------------------------------------------------------------

bool operator==(const Tuple& lhs, const Tuple& rhs)
{
  return std::abs(lhs.x - rhs.x) < EPSILON &&
         std::abs(lhs.y - rhs.y) < EPSILON &&
         std::abs(lhs.z - rhs.z) < EPSILON &&
         std::abs(lhs.w - rhs.w) < EPSILON; //
}

/// ---------------------------------------------------------------------------
/// @subsection Vector API
/// ---------------------------------------------------------------------------

float magnitude(Tuple v)
{
  return std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

Tuple normalize(Tuple v)
{
  auto mag = magnitude(v);
  return Tuple(v.x / mag, v.y / mag, v.z / mag, v.w / mag);
}

float dot(const Tuple& a, const Tuple& b)
{
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

Tuple cross(const Tuple& a, const Tuple& b)
{
  return Vector(               //
    (a.y * b.z) - (a.z * b.y), //
    (a.z * b.x) - (a.x * b.z), //
    (a.x * b.y) - (a.y * b.x)  //
  );
}

Tuple reflect(const Tuple& aVector, const Tuple& aNormal)
{
  return aVector - aNormal * 2 * dot(aVector, aNormal);
}

} // namespace RayTracer::Math
