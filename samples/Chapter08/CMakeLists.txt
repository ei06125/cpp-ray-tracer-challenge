add_executable(Chapter08)
file(GLOB_RECURSE Chapter08 "*.cpp")
target_sources(Chapter08 PUBLIC ${Chapter08})
target_compile_features(Chapter08 PUBLIC cxx_std_20)
target_link_libraries(Chapter08 PRIVATE RayTracer)
target_include_directories(Chapter08 PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                                             ${ROOT_DIR}/lib)
