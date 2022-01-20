add_executable(ProjectileDemo)
file(GLOB_RECURSE ProjectileDemo "*.cpp")
target_sources(ProjectileDemo PUBLIC ${ProjectileDemo})
target_compile_features(ProjectileDemo PUBLIC cxx_std_20)
target_link_libraries(ProjectileDemo PRIVATE RayTracer)
target_include_directories(ProjectileDemo PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                                                  ${ROOT_DIR}/lib)
