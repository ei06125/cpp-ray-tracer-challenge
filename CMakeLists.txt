cmake_minimum_required(VERSION 3.21)
project(RayTracerChallenge)

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
include(${ROOT_DIR}/tools/cmake/Modules/BuildToolsMain.cmake)

if(MSVC)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
      ${ROOT_DIR}/dist/Windows/bin/${CMAKE_BUILD_TYPE})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
      ${ROOT_DIR}/dist/Windows/lib/${CMAKE_BUILD_TYPE})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
      ${ROOT_DIR}/dist/Windows/lib/${CMAKE_BUILD_TYPE})
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
      ${ROOT_DIR}/dist/Linux/bin/${CMAKE_BUILD_TYPE})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
      ${ROOT_DIR}/dist/Linux/lib/${CMAKE_BUILD_TYPE})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
      ${ROOT_DIR}/dist/Linux/lib/${CMAKE_BUILD_TYPE})
endif()
set(USE_FOLDERS ON)

find_package(OpenMP REQUIRED)

add_library(GlobalSettings INTERFACE)
target_compile_features(GlobalSettings INTERFACE cxx_std_20)
target_link_libraries(GlobalSettings INTERFACE OpenMP::OpenMP_CXX)

add_library(RayTracerPCH OBJECT)
target_sources(RayTracerPCH PRIVATE ${ROOT_DIR}/lib/RayTracerPCH.cpp)
target_link_libraries(RayTracerPCH PUBLIC GlobalSettings)

add_subdirectory(external)
add_subdirectory(lib)
add_subdirectory(samples)
add_subdirectory(tests)
