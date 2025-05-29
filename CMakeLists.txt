cmake_minimum_required(VERSION 4.0.2 FATAL_ERROR)

project(p_0 VERSION 0.0.0 LANGUAGES CXX)

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/sysroot/${CMAKE_SYSTEM_NAME})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(options CONFIG REQUIRED)

if(P0_PREBUILD_SYSROOT)
    include(prebuild_dependency.cmake)
    return()
endif()

set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

add_library(p0_common INTERFACE)

if(P0_TEST_CODE_COVERAGE)
    target_compile_options(
        p0_common
        INTERFACE $<$<CXX_COMPILER_ID:Clang>:
                  -fprofile-instr-generate
                  -fcoverage-mapping
                  -fcoverage-mcdc
                  >
                  -coverage)
    target_link_options(p0_common INTERFACE -coverage)
endif()
add_library(p0::common ALIAS p0_common)

find_package(
    SDL3
    3.2.14
    EXACT
    CONFIG
    REQUIRED)

add_subdirectory(src)

include(CTest)
add_test(NAME coverage COMMAND $<TARGET_FILE:p0>)
