add_library(RayTracer)
file(GLOB_RECURSE RayTracer_SOURCES "RayTracer/*.cpp")
set(RayTracerLib_SOURCES
    ${RayTracer_SOURCES}
    PARENT_SCOPE)
target_sources(RayTracer PRIVATE ${RayTracer_SOURCES})
target_link_libraries(RayTracer PUBLIC GlobalSettings RayTracerPCH)
target_include_directories(RayTracer PUBLIC ${CMAKE_CURRENT_LIST_DIR}
                                            ${ROOT_DIR}/external)
set_target_properties(RayTracer PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
# target_precompile_headers(RayTracer PRIVATE "RayTracerPCH.hpp")
