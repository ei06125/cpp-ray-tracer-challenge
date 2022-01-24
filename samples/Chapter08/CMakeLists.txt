add_executable(Chapter08)
file(GLOB_RECURSE Chapter08_SOURCES "*.cpp")
target_sources(Chapter08 PUBLIC ${Chapter08_SOURCES})
target_link_libraries(Chapter08 PRIVATE RayTracer)
target_include_directories(Chapter08 PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                                             ${ROOT_DIR}/lib)
target_precompile_headers(Chapter08 REUSE_FROM RayTracer)
