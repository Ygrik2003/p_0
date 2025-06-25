cmake_minimum_required(VERSION 4.0.2)

add_executable(test_x11 test.cpp)
target_link_libraries(
    test_x11
    PRIVATE SDL3::SDL3
            X11::X11
            X11::Xext
            X11::Xtst)
