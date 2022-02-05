#pragma once
#include "RayTracerPCH.hpp"

#include <unordered_map>

namespace RayTracer {

// Forward declaration
namespace Math {
struct Tuple;
}

// Forward declaration
namespace Utils {
class OBJFile;
}

namespace Rendering {

// Forward declaration
namespace Primitives {
class Triangle;
}

namespace Parsers {
using namespace RayTracer::Math;
using namespace RayTracer::Utils;
using namespace RayTracer::Rendering::Primitives;

using OBJGroup = std::vector<std::shared_ptr<Triangle>>;
using OBJGroupMap = std::unordered_map<std::string, OBJGroup>;

class OBJParser
{
public:
  /// @section Member functions
  /// @subsection Special member functions
  OBJParser(const OBJFile& file);

  /// @subsection Observers
  int GetLinesIgnored() const;
  const std::vector<Tuple>& GetVertices() const;
  const std::vector<Tuple>& GetNormals() const;
  const OBJGroup& GetDefaultGroup() const;
  const OBJGroup& GetGroupByName(const std::string& name) const;
  const OBJGroupMap& GetGroupsMap() const;

private:
  void ParseVertex(const std::string& line);
  void ParseNormal(const std::string& line);
  void ParseFaces(const std::string& line);
  void ParseGroup(const std::string& line);

  std::string m_CurrentGroup{ "root" };
  int m_LinesIgnored{};
  std::vector<Tuple> m_Vertices{};
  std::vector<Tuple> m_Normals{};
  OBJGroupMap m_Groups;
};

} // namespace Parsers
} // namespace Rendering
} // namespace RayTracer
