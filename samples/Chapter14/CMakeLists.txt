add_executable(Chapter14)
file(GLOB_RECURSE Chapter14_SOURCES "*.cpp")
target_sources(Chapter14 PUBLIC ${Chapter14_SOURCES})
target_link_libraries(Chapter14 PRIVATE RayTracer)
target_include_directories(Chapter14 PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                                             ${ROOT_DIR}/lib)
target_precompile_headers(Chapter14 REUSE_FROM RayTracer)
