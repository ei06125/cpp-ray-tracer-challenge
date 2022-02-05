#pragma once
#include "RayTracerPCH.hpp"

#include "RayTracer/Math/Tuple.hpp"

namespace RayTracer::Rendering {
using namespace Math;

struct Canvas
{
public:
  /// @section Member functions
  Canvas(int w, int h);

  /// @subsection Iterators
  std::vector<Tuple>::iterator begin();
  std::vector<Tuple>::iterator end();

  /// @subsection Capacity
  std::size_t size() const;

  /// @subsection Observers
  const Tuple& pixel_at(int w, int h) const;

  /// @subsection Modifiers
  void write_pixel_at(int w, int h, const Tuple& color);

  /// @section Member data
  int width;
  int height;

private:
  std::vector<Tuple> pixels;
};

/// @section Non-member functions
void write_pixel(Canvas& c, int w, int h, const Tuple& color);

const Tuple& pixel_at(const Canvas& c, int w, int h);

std::string canvas_to_ppm(const Canvas& c);

} // namespace RayTracer::Rendering
