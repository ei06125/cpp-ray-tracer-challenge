cmake_minimum_required(VERSION 3.21)
project(RayTracerChallenge)

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

add_library(GlobalSettings INTERFACE)
target_compile_features(GlobalSettings INTERFACE cxx_std_20)

add_subdirectory(external)
add_subdirectory(lib)
add_subdirectory(samples)
add_subdirectory(tests)
