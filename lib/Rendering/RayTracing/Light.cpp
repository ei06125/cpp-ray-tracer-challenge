#include "Rendering/RayTracing/Light.hpp"

// C++ Standard Library
#include <iomanip>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const PointLight& aLight)
{
  os << "{ position:" << aLight.position << ", intensity:" << aLight.intensity
     << " }";
  return os;
}
