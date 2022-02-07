add_executable(Chapter09)
file(GLOB_RECURSE Chapter09_SOURCES "*.cpp")
target_sources(Chapter09 PUBLIC ${Chapter09_SOURCES})
target_link_libraries(Chapter09 PRIVATE RayTracer)
target_include_directories(Chapter09 PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                                             ${ROOT_DIR}/lib)
