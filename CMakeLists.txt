cmake_minimum_required(VERSION 4.0.2 FATAL_ERROR)

project(p_0 VERSION 0.0.0 LANGUAGES CXX)

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/sysroot/${CMAKE_SYSTEM_NAME})

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

if(P0_PREBUILD_SYSROOT)
    include(prebuild_dependency)
    return()
endif()

find_package(options CONFIG REQUIRED)
find_package(build_types CONFIG REQUIRED)

set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use it for global defines/flags. It target linked for all targets
add_library(p0_common INTERFACE)
add_library(p0::common ALIAS p0_common)

find_package(
    SDL3
    3.2.14
    EXACT
    CONFIG
    REQUIRED)

find_package(
    spdlog
    1.15.3
    EXACT
    CONFIG
    REQUIRED)

find_package(
    libassert
    2.1.5
    EXACT
    CONFIG
    REQUIRED)

find_package(
    doctest
    2.4.12
    EXACT
    REQUIRED)

find_package(X11 REQUIRED)

add_subdirectory(src)

include(CTest)
add_test(NAME coverage COMMAND $<TARGET_FILE:p0>)
