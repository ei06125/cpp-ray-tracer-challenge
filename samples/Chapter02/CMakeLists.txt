add_executable(Chapter02)
file(GLOB_RECURSE Chapter02_SOURCES "*.cpp")
target_sources(Chapter02 PRIVATE ${Chapter02_SOURCES})
target_link_libraries(Chapter02 PRIVATE RayTracer)
target_include_directories(Chapter02 PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                                             ${ROOT_DIR}/lib)
