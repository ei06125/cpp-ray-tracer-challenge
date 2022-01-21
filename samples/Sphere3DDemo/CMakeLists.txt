add_executable(Sphere3DDemo)
file(GLOB_RECURSE Sphere3DDemo "*.cpp")
target_sources(Sphere3DDemo PUBLIC ${Sphere3DDemo})
target_compile_features(Sphere3DDemo PUBLIC cxx_std_20)
target_link_libraries(Sphere3DDemo PRIVATE RayTracer)
target_include_directories(Sphere3DDemo PRIVATE ${CMAKE_CURRENT_LIST_DIR}
                                                ${ROOT_DIR}/lib)
