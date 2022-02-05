#pragma once
#include "RayTracerPCH.hpp"

namespace RayTracer {
namespace Utils {

class OBJFile
{
public:
  OBJFile(const char* filename)
    : m_Lines()
  {
    std::string line;
    std::ifstream file(filename);
    if (file.is_open()) {
      while (getline(file, line)) {
        m_Lines.push_back(std::move(line));
      }
      file.close();
    } else {
      throw std::runtime_error("Unable to open file");
    }
  }

  const std::vector<std::string>& GetLines() const { return m_Lines; }

private:
  std::vector<std::string> m_Lines;
};

} // namespace Utils
} // namespace RayTracer
