cmake_minimum_required(VERSION 3.21)
project(RayTracerChallenge)

set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(external)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)
