#pragma once

#include "RayTracer/Math/Tuple.hpp"

struct Canvas
{
public:
  Canvas(int w, int h);

  std::size_t size() const;
  std::vector<Tuple>::iterator begin();
  std::vector<Tuple>::iterator end();

  void write_pixel_at(int w, int h, const Tuple& color);
  const Tuple& pixel_at(int w, int h) const;

  bool isBlank() const;

  int width;
  int height;

private:
  std::vector<Tuple> pixels;
  bool m_IsBlank{ true };
};

void write_pixel(Canvas& c, int w, int h, const Tuple& color);

const Tuple& pixel_at(const Canvas& c, int w, int h);

std::string canvas_to_ppm(const Canvas& c);
