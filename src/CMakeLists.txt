cmake_minimum_required(VERSION 4.0.2)

add_subdirectory(overlay)

add_library(p0_base STATIC ${overlay_src})
target_link_libraries(p0_base PRIVATE SDL3::SDL3 PUBLIC p0::common)
add_library(p0::base ALIAS p0_base)

add_executable(p0 ${CMAKE_CURRENT_LIST_DIR}/main.cxx)
target_link_libraries(p0 PRIVATE p0::common p0::base)
