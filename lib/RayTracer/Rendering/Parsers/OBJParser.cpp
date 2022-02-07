#include "RayTracer/Rendering/Parsers/OBJParser.hpp"

#include "RayTracer/Core/Assertions.hpp"
#include "RayTracer/Math/Tuple.hpp"
#include "RayTracer/Rendering/Primitives/SmoothTriangle.hpp"
#include "RayTracer/Rendering/Primitives/Triangle.hpp"
#include "RayTracer/Utils/OBJFile.hpp"

namespace RayTracer {
namespace Rendering {
namespace Parsers {
using namespace RayTracer::Math;
using namespace RayTracer::Utils;
using namespace RayTracer::Rendering::Primitives;

/// ==========================================================================
/// @section Member functions
/// ==========================================================================

/// --------------------------------------------------------------------------
/// @subsection Special member functionsF
/// --------------------------------------------------------------------------

OBJParser::OBJParser(const OBJFile& file)
{
  m_Vertices.reserve(file.GetLines().size());
  // OBJ vertices are 1-based (NOT 0-based)
  m_Vertices.push_back(Point(0, 0, 0));

  m_Normals.reserve(file.GetLines().size());
  // OBJ normals are 1-based (NOT 0-based)
  m_Normals.push_back(Vector(0, 0, 0));

  for (const auto& line : file.GetLines()) {
    switch (line[0]) {
      case 'v':
        if (line[1] == 'n') {
          ParseNormal(line);
        } else {
          ParseVertex(line);
        }
        break;
      case 'f':
        ParseFaces(line);
        break;
      case 'g':
        ParseGroup(line);
        break;
      default:
        m_LinesIgnored++;
        break;
    }
  }
}

/// --------------------------------------------------------------------------
/// @subsection Observers
/// --------------------------------------------------------------------------

int OBJParser::GetLinesIgnored() const
{
  return m_LinesIgnored;
}

const std::vector<Tuple>& OBJParser::GetVertices() const
{
  return m_Vertices;
}

const std::vector<Tuple>& OBJParser::GetNormals() const
{
  return m_Normals;
}

const OBJGroup& OBJParser::GetDefaultGroup() const
{
  return m_Groups.at("root");
}

const OBJGroup& OBJParser::GetGroupByName(const std::string& name) const
{
  const static std::vector<std::shared_ptr<Triangle>> nil{};
  return m_Groups.contains(name) ? m_Groups.at(name) : nil;
}

const OBJGroupMap& OBJParser::GetGroupsMap() const
{
  return m_Groups;
}

///
/// @subsubsection Private member functions
///

void OBJParser::ParseVertex(const std::string& line)
{
  const std::string_view lineView = line;
  const std::string_view tupleView =
    lineView.substr(lineView.find_first_of(' ') + 1);

  const std::string_view xView =
    tupleView.substr(0, tupleView.find_first_of(' '));
  const std::string_view yView = tupleView.substr(
    tupleView.find_first_of(' ') + 1, tupleView.find_last_of(' ') - 3);
  const std::string_view zView =
    tupleView.substr(tupleView.find_last_of(' ') + 1);

  float x = std::atof(xView.data());
  float y = std::atof(yView.data());
  float z = std::atof(zView.data());

  m_Vertices.push_back(Point(x, y, z));
}

void OBJParser::ParseNormal(const std::string& line)
{
  const std::string_view lineView = line;
  const std::string_view tupleView =
    lineView.substr(lineView.find_first_of(' ') + 1);

  const std::string_view xView =
    tupleView.substr(0, tupleView.find_first_of(' '));
  const std::string_view yView = tupleView.substr(
    tupleView.find_first_of(' ') + 1, tupleView.find_last_of(' ') - 3);
  const std::string_view zView =
    tupleView.substr(tupleView.find_last_of(' ') + 1);

  float x = std::atof(xView.data());
  float y = std::atof(yView.data());
  float z = std::atof(zView.data());

  m_Normals.push_back(Vector(x, y, z));
}

void OBJParser::ParseFaces(const std::string& line)
{
  const std::string_view lineView = line;
  std::string_view verticesView =
    lineView.substr(lineView.find_first_of(' ') + 1);

  std::vector<std::size_t> vertexsIndices{};
#if TEXTURE_INDICES_ALLOWED
  std::vector<std::size_t> textureIndices{};
#endif
  std::vector<std::size_t> normalsIndices{};

  while (!verticesView.empty()) {
    std::string_view fView =
      verticesView.substr(0, verticesView.find_first_of(' '));

    // vertexsIndices
    std::string_view vIdxView = fView.substr(0, fView.find_first_of('/'));
    std::size_t vIndex = std::atoi(vIdxView.data());
    vertexsIndices.push_back(vIndex);

    if (fView.find('/') != std::string::npos) {
#if TEXTURE_INDICES_ALLOWED
      std::string_view tIdxView =
        fView.substr(fView.find_first_of('/') + 1, fView.find_last_of('/') - 2);
#endif
      // normalsIndices
      std::string_view nIdxView = fView.substr(fView.find_last_of('/') + 1);
      std::size_t nIndex = std::atoi(nIdxView.data());
      normalsIndices.push_back(nIndex);
    }

    auto firstWhitespacePos = verticesView.find_first_of(' ');
    if (firstWhitespacePos == std::string::npos) {
      break;
    } else {
      verticesView = verticesView.substr(firstWhitespacePos + 1);
    }
  }

  // Fan Triangulation
  for (auto i = 1U; i < vertexsIndices.size() - 1; ++i) {
    auto p1 = m_Vertices[vertexsIndices[0]];
    auto p2 = m_Vertices[vertexsIndices[i]];
    auto p3 = m_Vertices[vertexsIndices[i + 1]];
    // if parsing Triangles or Smooth Triangles
    if (normalsIndices.empty()) {
      auto tri = std::make_shared<Triangle>(p1, p2, p3);
      m_Groups[m_CurrentGroup].push_back(std::move(tri));
    } else {
      auto n1 = m_Normals[normalsIndices[0]];
      auto n2 = m_Normals[normalsIndices[i]];
      auto n3 = m_Normals[normalsIndices[i + 1]];
      auto tri = std::make_shared<SmoothTriangle>(p1, p2, p3, n1, n2, n3);
      m_Groups[m_CurrentGroup].push_back(std::move(tri));
    }
  }
}

void OBJParser::ParseGroup(const std::string& line)
{
  const std::string_view lineView = line;
  const std::string_view groupView =
    lineView.substr(lineView.find_first_of(' ') + 1);
  m_CurrentGroup = groupView;
}

} // namespace Parsers
} // namespace Rendering
} // namespace RayTracer
