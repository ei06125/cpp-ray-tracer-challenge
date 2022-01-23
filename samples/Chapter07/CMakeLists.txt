add_executable(Chapter07)
file(GLOB_RECURSE Chapter07 "*.cpp")
target_sources(Chapter07 PUBLIC ${Chapter07})
target_compile_features(Chapter07 PUBLIC cxx_std_20)
target_link_libraries(Chapter07 PRIVATE RayTracer)
target_include_directories(Chapter07 PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                                             ${ROOT_DIR}/lib)
