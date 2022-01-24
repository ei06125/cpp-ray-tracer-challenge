#include "RayTracer/Rendering/RayTracing/Light.hpp"

std::ostream& operator<<(std::ostream& os, const PointLight& aLight)
{
  os << "{ position:" << aLight.position << ", intensity:" << aLight.intensity
     << " }";
  return os;
}

bool operator==(const PointLight& lhs, const PointLight& rhs)
{
  return lhs.position == rhs.position && lhs.intensity == rhs.intensity;
}
