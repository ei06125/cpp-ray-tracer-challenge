add_executable(Sample07)
file(GLOB_RECURSE Sample07 "*.cpp")
target_sources(Sample07 PUBLIC ${Sample07})
target_compile_features(Sample07 PUBLIC cxx_std_20)
target_link_libraries(Sample07 PRIVATE RayTracer)
target_include_directories(Sample07 PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                                            ${ROOT_DIR}/lib)
