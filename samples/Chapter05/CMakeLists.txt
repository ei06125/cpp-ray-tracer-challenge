add_executable(Chapter05)
file(GLOB_RECURSE Chapter05 "*.cpp")
target_sources(Chapter05 PUBLIC ${Chapter05})
target_compile_features(Chapter05 PUBLIC cxx_std_20)
target_link_libraries(Chapter05 PRIVATE RayTracer)
target_include_directories(Chapter05 PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                                             ${ROOT_DIR}/lib)
