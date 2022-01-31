#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

#include "RayTracer/Profiling/TrackTime.hpp"

using namespace RayTracer::Profiling;

int main(int argc, char** argv)
{
  doctest::Context context;

  context.addFilter("test-case-exclude", "");
  context.setOption("rand-seed", 324);
  context.setOption("order-by", "rand"); // RANDOMIZE the test cases
  context.applyCommandLine(argc, argv);

  Timer testTimer("to test");
  int res = context.run();

  if (context.shouldExit()) {
    return res;
  }

  context.clearFilters();

  return res;
}
