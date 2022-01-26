#pragma once

#include "RayTracer/Math/Matrix.hpp"

namespace RayTracer::Math {

inline mat4 translation(float x, float y, float z)
{
  mat4 R = {
    1, 0, 0, x, //
    0, 1, 0, y, //
    0, 0, 1, z, //
    0, 0, 0, 1  //
  };

  return R;
}

inline mat4 scaling(float x, float y, float z)
{
  mat4 R = {
    x, 0, 0, 0, //
    0, y, 0, 0, //
    0, 0, z, 0, //
    0, 0, 0, 1  //
  };

  return R;
}

/** @param r radians */
inline mat4 rotation_x(float r)
{
  using namespace std;
  // clang-format off
  mat4 R = {
    1,      0,         0, 0,
    0, cos(r), -(sin(r)), 0,
    0, sin(r),    cos(r), 0,
    0,      0,         0, 1
  };
  // clang-format on

  return R;
}

/** @param r radians */
inline mat4 rotation_y(float r)
{
  using namespace std;
  // clang-format off
  mat4 R = {
     cos(r), 0, sin(r), 0,
          0, 1,      0, 0,
    -sin(r), 0, cos(r), 0,
          0, 0,      0, 1,
  };
  // clang-format on

  return R;
}

/** @param r radians */
inline mat4 rotation_z(float r)
{
  using namespace std;
  // clang-format off
  mat4 R = {
    cos(r), -sin(r), 0, 0,
    sin(r),  cos(r), 0, 0,
         0,       0, 1, 0,
         0,       0, 0, 1
  };
  // clang-format on

  return R;
}

inline mat4 shearing(float Xy, float Xz, float Yx, float Yz, float Zx, float Zy)
{
  mat4 R = {
    1,  Xy, Xz, 0, //
    Yx, 1,  Yz, 0, //
    Zx, Zy, 1,  0, //
    0,  0,  0,  1  //
  };

  return R;
}

inline mat4 view_transform(Tuple from, Tuple to, Tuple up)
{
  auto forward = normalize(to - from);
  auto left = cross(forward, normalize(up));
  auto true_up = cross(left, forward);

  mat4 orientation = {
    left.x,     left.y,     left.z,     0, //
    true_up.x,  true_up.y,  true_up.z,  0, //
    -forward.x, -forward.y, -forward.z, 0, //
    0,          0,          0,          1  //
  };

  return orientation * translation(-from.x, -from.y, -from.z);
}

} // namespace RayTracer::Math