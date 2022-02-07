#pragma once
#include "RayTracerPCH.hpp"

#include "RayTracer/Profiling/TrackTime.hpp"

namespace RayTracer {
namespace Profiling {
namespace CallStack {

class TrackCalls
{
public:
  TrackCalls(const char* functionSignature)
    : m_FunctionSignature(functionSignature)
    , m_Timer()
  {}

  ~TrackCalls() {}

private:
  const char* m_FunctionSignature;
  Timer m_Timer;
};

} // namespace CallStack
} // namespace Profiling
} // namespace RayTracer

#ifdef _MSC_VER
#define FUNCTION_SIGNATURE __FUNCSIG__
#else
#define FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#endif

#define TRACE
#ifdef TRACE
#define TRACE_FUNCTION() puts(FUNCTION_SIGNATURE)
#else
#define TRACE_FUNCTION() (void)0
#endif
