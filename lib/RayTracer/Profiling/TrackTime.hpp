#pragma once

#include "RayTracer/Utils/Print.hpp"

#include <chrono>
#include <string>

namespace RayTracer {
namespace Profiling {

class Timer
{
public:
  /// @section Member types
  using Clock = std::chrono::high_resolution_clock;
  using TimePoint = std::chrono::time_point<Clock>;
  using Ms = std::chrono::milliseconds;

  /// @section Member classes

  /// @section Member functions
  explicit Timer(const char* actionString = "")
    : m_ActionString(actionString)
    , m_Start(Clock::now())
    , m_End(m_Start)
  {}
  Timer(const Timer&) = default;
  Timer(Timer&&) noexcept = default;
  Timer& operator=(const Timer&) = default;
  Timer& operator=(Timer&&) noexcept = default;

  ~Timer() { status(); }

  void status()
  {
    this->m_End = Clock::now();
    auto diff = m_End - m_Start;
    auto miliseconds = std::chrono::duration_cast<Ms>(diff);
    Print("Took", miliseconds.count(), "miliseconds", m_ActionString);
  }

private:
  const char* m_ActionString;
  TimePoint m_Start{};
  TimePoint m_End{};
};

} // namespace Profiling
} // namespace RayTracer
