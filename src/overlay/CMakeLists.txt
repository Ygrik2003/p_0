cmake_minimum_required(VERSION 4.0.2)

set(overlay_src
    ${CMAKE_CURRENT_LIST_DIR}/overlay_x11.cxx
    ${CMAKE_CURRENT_LIST_DIR}/overlay_x11.h ${CMAKE_CURRENT_LIST_DIR}/main.cxx
    PARENT_SCOPE)
