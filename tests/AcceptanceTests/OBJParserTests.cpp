// Test Framework
#include "doctest/doctest.h"

// Engine
#include "RayTracer.hpp"

using namespace RayTracer::Math;
using namespace RayTracer::Rendering::Primitives;
using namespace RayTracer::Rendering::Parsers;

#define GET_THIS_FILE_ABSOLUTE_PATH() __FILE__
std::filesystem::path GetTestAssetsAbsolutePath()
{
  static auto path = std::filesystem::path(GET_THIS_FILE_ABSOLUTE_PATH())
                       .parent_path()
                       .append("assets")
                       .append("scenes");
  return path;
}

SCENARIO("Ignoring unrecognized lines")
{
  GIVEN("gibberish = a file containing:\
    \n\t    \"\"\"\
    \n\t    There was a young lady named Bright\
    \n\t    who traveled much faster than light.\
    \n\t    She set out one day\
    \n\t    in a relative way,\
    \n\t    and came back the previous night.\
    \n\t    \"\"\"")
  {
    auto filePath = GetTestAssetsAbsolutePath().append("Gibberish.obj");
    auto gibberish = OBJFile(filePath.string().c_str());

    WHEN("parser = parse_obj_file(gibberish)")
    {
      OBJParser parser(gibberish);
      THEN("parser should have ignored 5 lines")
      {
        CHECK(parser.GetLinesIgnored() == 5);
      }
    }
  }
}

SCENARIO("Vertex records")
{
  GIVEN("file = a file containing:\
    \n\t    \"\"\"\
    \n\t    v -1 1 0\
    \n\t    v -1.0000 0.5000 0.0000\
    \n\t    v 1 0 0\
    \n\t    v 1 1 0\
    \n\t    \"\"\"")
  {
    auto filePath = GetTestAssetsAbsolutePath().append("VertexRecords.obj");
    auto file = OBJFile(filePath.string().c_str());

    WHEN("parser = parse_obj_file(file)")
    {
      OBJParser parser(file);
      THEN("parser.vertices[1] == point(-1, 1, 0)\
      \n\t And parser.vertices[2] == point(-1, 0.5, 0)\
      \n\t And parser.vertices[3] == point(1, 0, 0)\
      \n\t And parser.vertices[4] == point(1, 1, 0)")
      {
        REQUIRE(parser.GetVertices().size() == 5);
        CHECK(parser.GetVertices()[1] == Point(-1, 1, 0));
        CHECK(parser.GetVertices()[2] == Point(-1, 0.5, 0));
        CHECK(parser.GetVertices()[3] == Point(1, 0, 0));
        CHECK(parser.GetVertices()[4] == Point(1, 1, 0));
      }
    }
  }
}

SCENARIO("Parsing triangle faces")
{
  GIVEN("file = a file containing:\
    \n\t    \"\"\"\
    \n\t    v -1 1 0\
    \n\t    v -1 0 0\
    \n\t    v 1 0 0\
    \n\t    v 1 1 0\
    \n\t    \
    \n\t    f 1 2 3\
    \n\t    f 1 3 4\
    \n\t    \"\"\"")
  {
    auto filePath = GetTestAssetsAbsolutePath().append("TriangleFaces.obj");
    auto file = OBJFile(filePath.string().c_str());

    WHEN("parser = parse_obj_file(file)\
    \n\t  And g = parser.default_group\
    \n\t  And t1 = first child of g\
    \n\t  And t2 = second child of g")
    {
      OBJParser parser(file);
      auto g = parser.GetDefaultGroup();
      REQUIRE(g.size() == 2);
      auto t1 = g[0];
      auto t2 = g[1];

      THEN("t1.p1 == parser.vertices[1]\
      \n\t  And t1.p2 == parser.vertices[2]\
      \n\t  And t1.p3 == parser.vertices[3]\
      \n\t  And t2.p1 == parser.vertices[1]\
      \n\t  And t2.p2 == parser.vertices[3]\
      \n\t  And t2.p3 == parser.vertices[4]\
      ")
      {
        REQUIRE(parser.GetVertices().size() == 5);
        CHECK(t1->p1 == parser.GetVertices()[1]);
        CHECK(t1->p2 == parser.GetVertices()[2]);
        CHECK(t1->p3 == parser.GetVertices()[3]);
        CHECK(t2->p1 == parser.GetVertices()[1]);
        CHECK(t2->p2 == parser.GetVertices()[3]);
        CHECK(t2->p3 == parser.GetVertices()[4]);
      }
    }
  }
}

SCENARIO("Triangulating polygons")
{
  GIVEN("file = a file containing:\
    \n\t    \"\"\"\
    \n\t    v -1 1 0\
    \n\t    v -1 0 0\
    \n\t    v 1 0 0\
    \n\t    v 1 1 0\
    \n\t    v 0 2 0\
    \n\t    \
    \n\t    f 1 2 3 4 5\
    \n\t    \"\"\"")
  {
    auto filePath =
      GetTestAssetsAbsolutePath().append("TriangulatingPolygons.obj");
    auto file = OBJFile(filePath.string().c_str());

    WHEN("parser = parse_obj_file(file)\
    \n\t  And g = parser.default_group\
    \n\t  And t1 = first child of g\
    \n\t  And t2 = second child of g\
    \n\t  And t3 = third child of g")
    {
      OBJParser parser(file);
      auto g = parser.GetDefaultGroup();
      REQUIRE(g.size() == 3);
      auto t1 = g[0]; // f 1, 2, 3
      auto t2 = g[1]; // f 1, 3, 4
      auto t3 = g[2]; // f 1, 4, 5

      THEN("t1.p1 == parser.vertices[1]\
      \n\t  And t1.p2 == parser.vertices[2]\
      \n\t  And t1.p3 == parser.vertices[3]\
      \n\t  And t2.p1 == parser.vertices[1]\
      \n\t  And t2.p2 == parser.vertices[3]\
      \n\t  And t2.p3 == parser.vertices[4]\
      \n\t  And t3.p1 == parser.vertices[1]\
      \n\t  And t3.p2 == parser.vertices[4]\
      \n\t  And t3.p3 == parser.vertices[5]\
      ")
      {
        REQUIRE(parser.GetVertices().size() == 6);
        CHECK(t1->p1 == parser.GetVertices()[1]);
        CHECK(t1->p2 == parser.GetVertices()[2]);
        CHECK(t1->p3 == parser.GetVertices()[3]);
        CHECK(t2->p1 == parser.GetVertices()[1]);
        CHECK(t2->p2 == parser.GetVertices()[3]);
        CHECK(t2->p3 == parser.GetVertices()[4]);
        CHECK(t3->p1 == parser.GetVertices()[1]);
        CHECK(t3->p2 == parser.GetVertices()[4]);
        CHECK(t3->p3 == parser.GetVertices()[5]);
        ;
      }
    }
  }
}

SCENARIO("Triangles in groups")
{
  GIVEN("file = the file 'triangles.obj'")
  {
    auto filePath = GetTestAssetsAbsolutePath().append("Triangles.obj");
    auto file = OBJFile(filePath.string().c_str());

    WHEN("parser = parser_obj_file(file)\
    \n\t  And g1 = 'FirstGroup' from parser\
    \n\t  And g2 = 'SecondGroup' from parser\
    \n\t  And t1 = first child of g1\
    \n\t  And t2 = first child of g2")
    {
      OBJParser parser(file);
      auto g1 = parser.GetGroupByName("FirstGroup");
      auto g2 = parser.GetGroupByName("SecondGroup");
      REQUIRE(g1.size() == 1);
      REQUIRE(g2.size() == 1);
      auto t1 = g1[0];
      auto t2 = g2[0];

      THEN("t1.p1 == parser.vertices[1]\
      \n\t  And t1.p2 == parser.vertices[2]\
      \n\t  And t1.p3 == parser.vertices[3]\
      \n\t  And t2.p1 == parser.vertices[1]\
      \n\t  And t2.p2 == parser.vertices[3]\
      \n\t  And t2.p3 == parser.vertices[4]\
      ")
      {
        REQUIRE(parser.GetVertices().size() == 5);
        CHECK(t1->p1 == parser.GetVertices()[1]);
        CHECK(t1->p2 == parser.GetVertices()[2]);
        CHECK(t1->p3 == parser.GetVertices()[3]);
        CHECK(t2->p1 == parser.GetVertices()[1]);
        CHECK(t2->p2 == parser.GetVertices()[3]);
        CHECK(t2->p3 == parser.GetVertices()[4]);
        ;
      }
    }
  }
}

SCENARIO("Converting an OBJ file to a group")
{
  GIVEN("file = the file 'triangles.obj'\
  \n\t  And parser = parse_obj_file(file)")
  {
    auto filePath = GetTestAssetsAbsolutePath().append("Triangles.obj");
    auto file = OBJFile(filePath.string().c_str());
    OBJParser parser(file);

    WHEN("g = obj_to_group(parser)")
    {
      auto g = parser.GetGroupsMap();

      THEN("g includes 'FirstGroup' from parser\
      \n\t  And g includes 'SecondGroup' from parser")
      {
        auto firstGroup = parser.GetGroupByName("FirstGroup");
        auto secondGroup = parser.GetGroupByName("SecondGroup");
        CHECK(g.contains("FirstGroup"));
        CHECK(g.contains("SecondGroup"));
        CHECK(g.at("FirstGroup") == firstGroup);
        CHECK(g.at("SecondGroup") == secondGroup);
      }
    }
  }
}

SCENARIO("Vertex normal records")
{
  GIVEN("file = a file containing:\
    \n\t    \"\"\"\
    \n\t    vn 0 0 1\
    \n\t    vn 0.707 0 -0.707\
    \n\t    vn 1 2 3\
    \n\t    \"\"\"")
  {
    auto filePath =
      GetTestAssetsAbsolutePath().append("VertexNormalRecords.obj");
    auto file = OBJFile(filePath.string().c_str());

    WHEN("parser = parse_obj_file(file)")
    {
      OBJParser parser(file);
      THEN("parser.normals[1] == vector(0, 0, 1)\
      \n\t And parser.normals[2] == vector(0.707, 0, -0.707)\
      \n\t And parser.normals[3] == vector(1, 2, 3)")
      {
        REQUIRE(parser.GetNormals().size() == 4);
        CHECK(parser.GetNormals()[1] == Vector(0, 0, 1));
        CHECK(parser.GetNormals()[2] == Vector(0.707, 0, -0.707));
        CHECK(parser.GetNormals()[3] == Vector(1, 2, 3));
      }
    }
  }
}

SCENARIO("Faces with normals")
{
  GIVEN("file = a file containing:\
    \n\t    \"\"\"\
    \n\t    v 0 1 0\
    \n\t    v -1 0 0\
    \n\t    v 1 0 0\
    \n\t    \
    \n\t    vn -1 0 0\
    \n\t    vn 1 0 0\
    \n\t    vn 0 1 0\
    \n\t    \
    \n\t    f 1//3 2//1 3//2\
    \n\t    f 1/0/3 2/102/1 3/14/2\
    \n\t    \"\"\"")
  {
    auto filePath = GetTestAssetsAbsolutePath().append("FacesWithNormals.obj");
    auto file = OBJFile(filePath.string().c_str());

    WHEN("parser = parse_obj_file(file)\
    \n\t And g = parser.default_group\
    \n\t And t1 = first child of g\
    \n\t And t2 = second child of g")
    {
      OBJParser parser(file);
      auto g = parser.GetDefaultGroup();
      REQUIRE(g.size() == 2);
      auto t1 = std::static_pointer_cast<SmoothTriangle>(g[0]);
      auto t2 = std::static_pointer_cast<SmoothTriangle>(g[1]);

      THEN("t1.p1 == parser.vertices[1]\
      \n\t And t1.p2 == parser.vertices[2]\
      \n\t And t1.p3 == parser.vertices[3]\
      \n\t And t1.n1 == parser.normals[3]\
      \n\t And t1.n2 == parser.normals[1]\
      \n\t And t1.n3 == parser.normals[2]\
      \n\t And t2 == t1")
      {
        REQUIRE(parser.GetVertices().size() == 4);
        CHECK(t1->p1 == parser.GetVertices()[1]);
        CHECK(t1->p2 == parser.GetVertices()[2]);
        CHECK(t1->p3 == parser.GetVertices()[3]);
        REQUIRE(parser.GetNormals().size() == 4);
        CHECK(t1->n1 == parser.GetNormals()[3]);
        CHECK(t1->n2 == parser.GetNormals()[1]);
        CHECK(t1->n3 == parser.GetNormals()[2]);
        CHECK(*t2.get() == *t1.get());
      }
    }
  }
}
