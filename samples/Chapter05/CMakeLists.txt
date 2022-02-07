add_executable(Chapter05)
file(GLOB_RECURSE Chapter05_SOURCES "*.cpp")
target_sources(Chapter05 PUBLIC ${Chapter05_SOURCES})
target_link_libraries(Chapter05 PRIVATE RayTracer)
target_include_directories(Chapter05 PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                                             ${ROOT_DIR}/lib)
