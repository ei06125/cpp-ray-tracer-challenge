#include "RayTracer/Rendering/Color.hpp"

#include "RayTracer/Math/Constants.hpp"

namespace RayTracer::Rendering::Colors {
using namespace RayTracer::Math::Constants;

/// ===========================================================================
/// @section Non-member functions
/// ===========================================================================

/// ---------------------------------------------------------------------------
/// @subsection Arithmetic operators
/// ---------------------------------------------------------------------------

Color operator+(const Color& lhs, const Color& rhs)
{
  return { lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b };
}

Color operator-(const Color& lhs, const Color& rhs)
{
  return { lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b };
}

Color operator*(const Color& lhs, const Color& rhs)
{
  return { lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b };
}

Color operator*(const Color& lhs, float scalar)
{
  return { lhs.r * scalar, lhs.g * scalar, lhs.b * scalar };
}

std::ostream& operator<<(std::ostream& os, const Color& c)
{
  os << "{ r:" << std::fixed << std::setprecision(7) << c.r << ", g:" << c.g
     << ", b:" << c.b << " }";
  return os;
}

/// ---------------------------------------------------------------------------
/// @subsection Logic operators
/// ---------------------------------------------------------------------------

bool operator==(const Color& lhs, const Color& rhs)
{
  return std::abs(lhs.r - rhs.r) < EPSILON &&
         std::abs(lhs.g - rhs.g) < EPSILON &&
         std::abs(lhs.b - rhs.b) < EPSILON; //
}

/// ---------------------------------------------------------------------------
/// @subsection Color API
/// ---------------------------------------------------------------------------

int Saturate(float f)
{
  return static_cast<int>(std::clamp(f * 256.0f, 0.0f, 255.0f));
}

} // namespace RayTracer::Rendering::Colors