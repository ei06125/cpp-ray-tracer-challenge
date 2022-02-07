add_executable(Chapter06)
file(GLOB_RECURSE Chapter06_SOURCES "*.cpp")
target_sources(Chapter06 PUBLIC ${Chapter06_SOURCES})
target_link_libraries(Chapter06 PRIVATE RayTracer)
target_include_directories(Chapter06 PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                                             ${ROOT_DIR}/lib)
