add_executable(Chapter06)
file(GLOB_RECURSE Chapter06 "*.cpp")
target_sources(Chapter06 PUBLIC ${Chapter06})
target_compile_features(Chapter06 PUBLIC cxx_std_20)
target_link_libraries(Chapter06 PRIVATE RayTracer)
target_include_directories(Chapter06 PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                                             ${ROOT_DIR}/lib)
