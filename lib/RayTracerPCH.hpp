#pragma once

/// ===========================================================================
/// @section C Standard Library
#include <cassert>
#include <cmath>
#include <cstdio>  // for printf()
#include <cstdlib> // for malloc() and aligned_alloc()
#include <cstring>

/// ===========================================================================
/// @section C++ Standard Library
#include <algorithm>
#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <locale>
#include <memory>
#include <new> // for std::align_val_t
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

/// ===========================================================================
/// @section Windows specializations
#ifdef _MSC_VER
#include <malloc.h> // for _aligned_malloc() and _aligned_free()
#endif
