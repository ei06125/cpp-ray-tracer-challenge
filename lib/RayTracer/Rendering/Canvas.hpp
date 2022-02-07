#pragma once
#include "RayTracerPCH.hpp"

#include "RayTracer/Rendering/Color.hpp"

namespace RayTracer::Rendering {
using namespace Colors;

struct Canvas
{
public:
  /// @section Member functions
  Canvas(int w, int h);

  /// @subsection Iterators
  std::vector<Color>::iterator begin();
  std::vector<Color>::iterator end();

  /// @subsection Capacity
  std::size_t size() const;

  /// @subsection Observers
  const Color& pixel_at(int w, int h) const;

  /// @subsection Modifiers
  void write_pixel_at(int w, int h, const Color& color);

  /// @section Member data
  int width;
  int height;

private:
  std::vector<Color> pixels;
};

/// @section Non-member functions
void write_pixel(Canvas& c, int w, int h, const Color& color);

const Color& pixel_at(const Canvas& c, int w, int h);

std::string canvas_to_ppm(const Canvas& c);

} // namespace RayTracer::Rendering
