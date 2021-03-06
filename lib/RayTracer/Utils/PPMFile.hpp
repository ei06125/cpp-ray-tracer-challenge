#pragma once
#include "RayTracerPCH.hpp"

class PPMFile
{
public:
  PPMFile(const char* filename)
    : m_FileHandle(fopen(filename, "w"))
  {}
  ~PPMFile() { fclose(m_FileHandle); }

  void Write(const char* data) { fprintf(m_FileHandle, "%s\n", data); }

private:
  FILE* m_FileHandle;
};
