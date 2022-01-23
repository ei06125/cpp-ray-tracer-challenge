add_executable(Chapter02)
file(GLOB_RECURSE Chapter02 "*.cpp")
target_sources(Chapter02 PUBLIC ${Chapter02})
target_compile_features(Chapter02 PUBLIC cxx_std_20)
target_link_libraries(Chapter02 PRIVATE RayTracer)
target_include_directories(Chapter02 PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                                                  ${ROOT_DIR}/lib)
