add_executable(Chapter10)
file(GLOB_RECURSE Chapter10_SOURCES "*.cpp")
target_sources(Chapter10 PUBLIC ${Chapter10_SOURCES})
target_link_libraries(Chapter10 PRIVATE RayTracer)
target_include_directories(Chapter10 PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                                             ${ROOT_DIR}/lib)
