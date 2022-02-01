add_executable(RayTracerAcceptanceTests)
file(GLOB_RECURSE RayTracerAcceptanceTests_SOURCES "*.cpp")
target_sources(RayTracerAcceptanceTests
               PRIVATE ${RayTracerAcceptanceTests_SOURCES})
target_link_libraries(RayTracerAcceptanceTests PRIVATE RayTracer
                                                       doctest::doctest)
target_include_directories(RayTracerAcceptanceTests PRIVATE ${ROOT_DIR}/lib)
target_precompile_headers(RayTracerAcceptanceTests REUSE_FROM RayTracer)

add_dependencies(RayTracerAcceptanceTests RayTracer)
