/// @copyright Vandevoorde, Josuttis, Gregor.

#pragma once

namespace RayTracer {
namespace Profiling {
namespace Memory {

class TrackNew
{
private:
  inline static int numMalloc = 0;    // num malloc calls
  inline static size_t sumSize = 0;   // bytes allocated so far
  inline static bool doTrace = false; // tracing enabled
  inline static bool inNew = false;   // don't track output inside new overloads
public:
  static void reset()
  { // reset new/memory counters
    numMalloc = 0;
    sumSize = 0;
  }

  static void trace(bool b)
  { // enable/disable tracing
    doTrace = b;
  }

  // implementation of tracked allocation:
  static void* allocate(std::size_t size, std::size_t align, const char* call)
  {
    // track and trace the allocation:
    ++numMalloc;
    sumSize += size;
    void* p;
    if (align == 0) {
      p = std::malloc(size);
    } else {
#ifdef _MSC_VER
      p = _aligned_malloc(size, align); // Windows API
#else
      p = std::aligned_alloc(align, size); // C++17 API
#endif
    }
    if (doTrace) {
      // DON'T use std::cout here because it might allocate memory
      // while we are allocating memory (core dump at best)
      printf("#%d %s ", numMalloc, call);
      printf("(%zu bytes, ", size);
      if (align > 0) {
        printf("%zu-bytes aligned) ", align);
      } else {
        printf("def-aligned) ");
      }
      printf("=> %p (total: %zu Bytes)\n", (void*)p, sumSize);
    }
    return p;
  }

  static void status()
  { // print current state
    printf("%d allocations for %zu bytes\n", numMalloc, sumSize);
  }

  struct StatusData
  {
    int mallocNum;
    size_t sizeSum;
  };
  static StatusData getStatus() { return { numMalloc, sumSize }; }
};

} // namespace Memory
} // namespace Profiling
} // namespace RayTracer

using namespace RayTracer::Profiling::Memory;

[[nodiscard]] inline void* operator new(std::size_t size)
{
  return TrackNew::allocate(size, 0, "::new");
}

[[nodiscard]] inline void* operator new(std::size_t size,
                                        std::align_val_t align)
{
  return TrackNew::allocate(size, static_cast<size_t>(align), "::new aligned");
}

[[nodiscard]] inline void* operator new[](std::size_t size)
{
  return TrackNew::allocate(size, 0, "::new[]");
}

[[nodiscard]] inline void* operator new[](std::size_t size,
                                          std::align_val_t align)
{
  return TrackNew::allocate(
    size, static_cast<size_t>(align), "::new[] aligned");
}

// ensure deallocations match:
inline void operator delete(void* p) noexcept
{
  std::free(p);
}

inline void operator delete(void* p, std::size_t) noexcept
{
  ::operator delete(p);
}

inline void operator delete(void* p, std::align_val_t) noexcept
{
#ifdef _MSC_VER
  _aligned_free(p); // Windows API
#else
  std::free(p);                            // C++17 API
#endif
}

inline void operator delete(void* p,
                            std::size_t,
                            std::align_val_t align) noexcept
{
  ::operator delete(p, align);
}
