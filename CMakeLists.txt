cmake_minimum_required(VERSION 4.0.2 FATAL_ERROR)

project(p_0 VERSION 0.0.0 LANGUAGES CXX)

if(P0_PREBUILD_SYSROOT)
    include(cmake/prebuild_dependency.cmake)
    return()
endif()
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/sysroot/${CMAKE_SYSTEM_NAME})

set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

find_package(
    SDL3
    3.2.14
    EXACT
    CONFIG
    REQUIRED)

add_subdirectory(src)
