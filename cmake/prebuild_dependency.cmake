cmake_minimum_required(VERSION 4.0.2 FATAL_ERROR)

cmake_path(
    GET
    CMAKE_SOURCE_DIR
    PARENT_PATH
    parent_dir)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/sysroot/${CMAKE_SYSTEM_NAME})
set(external_sources_dir ${parent_dir}/external)

include(ExternalProject)

externalproject_add(
    sdl
    SOURCE_DIR ${external_sources_dir}/sdl
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-3.2.14
    CMAKE_GENERATOR "Ninja Multi-Config"
    BUILD_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --config $<CONFIG>
    CMAKE_ARGS --fresh
               -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
               -DCMAKE_DEBUG_POSTFIX:STRING=d
               -DSDL_STATIC:BOOL=OFF
               -DSDL_SHARED:BOOL=ON
               -DSDL_TESTS:BOOL=OFF)

externalproject_add(
    spdlog
    SOURCE_DIR ${external_sources_dir}/spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG v1.15.3
    CMAKE_GENERATOR "Ninja Multi-Config"
    BUILD_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --config $<CONFIG>
    CMAKE_ARGS --fresh -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
               -DCMAKE_DEBUG_POSTFIX:STRING=d)

externalproject_add(
    libassert
    SOURCE_DIR ${external_sources_dir}/libassert
    GIT_REPOSITORY https://github.com/jeremy-rifkin/libassert
    GIT_TAG v2.1.5
    BUILD_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR>
    CMAKE_ARGS --fresh -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
               -DCMAKE_BUILD_TYPE:STRING=Release)

externalproject_add(
    doctest
    SOURCE_DIR ${external_sources_dir}/doctest
    GIT_REPOSITORY https://github.com/doctest/doctest
    GIT_TAG v2.4.12
    CMAKE_GENERATOR "Ninja Multi-Config"
    BUILD_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --config $<CONFIG>
    CMAKE_ARGS --fresh -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
               -DCMAKE_DEBUG_POSTFIX:STRING=d)
