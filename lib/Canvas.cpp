#include "Canvas.hpp"

#include <algorithm>
#include <stdexcept>

Canvas::Canvas(int w, int h)
  : width(w)
  , height(h)
{
  pixels.reserve(width * height);
  for (std::size_t i = 0; i < pixels.capacity(); ++i) {
    pixels.push_back(make_color(0, 0, 0));
  }
}

std::size_t Canvas::size() const
{
  return pixels.size();
}

std::vector<Tuple>::iterator Canvas::begin()
{
  return pixels.begin();
}

std::vector<Tuple>::iterator Canvas::end()
{
  return pixels.end();
}

void Canvas::write_pixel_at(int w, int h, const Tuple& color)
{
  pixels.at(h * width + w) = color;
  m_IsBlank = false;
}

const Tuple& Canvas::pixel_at(int w, int h) const
{
  return pixels.at(h * width + w);
}

bool Canvas::isBlank() const
{
  return m_IsBlank;
}

void write_pixel(Canvas& c, int w, int h, const Tuple& color)
{
  c.write_pixel_at(w, h, color);
}

const Tuple& pixel_at(const Canvas& c, int w, int h)
{
  return c.pixel_at(w, h);
}

std::string canvas_to_ppm(const Canvas& c)
{
  std::string result{};

  // PPM Header
  result += "P3\n";
  result += std::to_string(c.width) + " " + std::to_string(c.height) + "\n";
  result += std::to_string(255) + "\n";

  // PPM Body
  if (!c.isBlank()) {
    for (auto row = 0U; row < c.height; ++row) {
      for (auto col = 0U; col < c.width; ++col) {
        const auto& color = c.pixel_at(col, row);
        result +=
          std::to_string((int)(std::clamp(color.red * 256, 0.0f, 255.0f))) +
          " ";
        result +=
          std::to_string((int)(std::clamp(color.green * 256, 0.0f, 255.0f))) +
          " ";
        result +=
          std::to_string((int)(std::clamp(color.blue * 256, 0.0f, 255.0f)));
        if (col < c.width - 1) {
          result += " ";
        }
      }
      result += "\n";
    }
    result += "\n";
  }

  return result;
}
