add_executable(SilhouetteDemo)
file(GLOB_RECURSE SilhouetteDemo "*.cpp")
target_sources(SilhouetteDemo PUBLIC ${SilhouetteDemo})
target_compile_features(SilhouetteDemo PUBLIC cxx_std_20)
target_link_libraries(SilhouetteDemo PRIVATE RayTracer)
target_include_directories(SilhouetteDemo PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                                                  ${ROOT_DIR}/lib)
