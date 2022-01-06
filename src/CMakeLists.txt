add_executable(TechDemo)
file(GLOB_RECURSE TechDemo_SOURCES "*.cpp")
file(GLOB_RECURSE TechDemo_HEADERS "*.hpp")
target_sources(TechDemo PUBLIC ${TechDemo_SOURCES})
target_compile_features(TechDemo PUBLIC cxx_std_20)
target_link_libraries(TechDemo PRIVATE RayTracer)
target_include_directories(TechDemo PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                                            ${ROOT_DIR}/lib)
