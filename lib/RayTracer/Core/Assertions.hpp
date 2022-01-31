#pragma once

#ifdef NDEBUG
#define DEBUG_ASSERT(expr)
#else
#include <cassert>
#define DEBUG_ASSERT(expr) assert(expr)
#endif
