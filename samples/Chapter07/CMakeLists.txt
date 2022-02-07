add_executable(Chapter07)
file(GLOB_RECURSE Chapter07_SOURCES "*.cpp")
target_sources(Chapter07 PUBLIC ${Chapter07_SOURCES})
target_link_libraries(Chapter07 PRIVATE RayTracer)
target_include_directories(Chapter07 PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                                             ${ROOT_DIR}/lib)
