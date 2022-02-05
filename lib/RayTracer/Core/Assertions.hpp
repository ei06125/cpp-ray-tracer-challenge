#pragma once
#include "RayTracerPCH.hpp"

#ifdef NDEBUG
#define DEBUG_ASSERT(expr)
#else
#include <cassert>
#define DEBUG_ASSERT(expr) assert(expr)
#endif
