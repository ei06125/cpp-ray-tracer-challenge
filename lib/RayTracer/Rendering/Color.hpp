#pragma once
#include "RayTracerPCH.hpp"

namespace RayTracer::Rendering::Colors {

struct Color
{
  float r{ 1.0f };
  float g{ 1.0f };
  float b{ 1.0f };
  // float a{ 1.0f };
};

/// @section Non-member functions

/// @subsection Arithmetic operators

Color operator+(const Color& lhs, const Color& rhs);
Color operator-(const Color& lhs, const Color& rhs);
Color operator*(const Color& lhs, const Color& rhs);
Color operator*(const Color& lhs, float scalar);
std::ostream& operator<<(std::ostream& os, const Color& c);

/// @subsection Logic operators

bool operator==(const Color& lhs, const Color& rhs);

/// @subsection Color API

int Saturate(float f);

/// @section Constants

constexpr Color Black = Color{ 0.0f, 0.0f, 0.0f };
constexpr Color White = Color{ 1.0f, 1.0f, 1.0f };

constexpr Color Red = Color{ 1.0f, 0.0f, 0.0f };
constexpr Color Green = Color{ 0.0f, 1.0f, 0.0f };
constexpr Color Blue = Color{ 0.0f, 0.0f, 1.0f };

constexpr Color Yellow = Color{ 1.0f, 1.0f, 0.0f };
constexpr Color Cyan = Color{ 0.0f, 1.0f, 1.0f };
constexpr Color Mangenta = Color{ 1.0f, 0.0f, 1.0f };

} // namespace RayTracer::Rendering::Colors
