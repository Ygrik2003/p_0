cmake_minimum_required(VERSION 4.0.2 FATAL_ERROR)

cmake_path(
    GET
    CMAKE_SOURCE_DIR
    PARENT_PATH
    parent_dir)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/sysroot)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/sysroot)
set(sources_dir ${parent_dir}/external)

include(ExternalProject)

externalproject_add(
    sdl
    SOURCE_DIR ${sources_dir}/sdl
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-3.2.14
    CMAKE_GENERATOR "Ninja Multi-Config"
    BUILD_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --config $<CONFIG>
    CMAKE_ARGS --fresh
               -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
               -DCMAKE_DEBUG_POSTFIX:STRING=d
               -DSDL_STATIC:BOOL=ON
               -DSDL_SHARED:BOOL=OFF)
