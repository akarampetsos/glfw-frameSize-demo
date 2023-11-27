cmake_minimum_required(VERSION 3.16)

project(
    glfw-frameSize-demo
    LANGUAGES C
)

include(cmake/prevent-out-of-source-build.cmake)

add_subdirectory(extern)
add_subdirectory(libs)
add_subdirectory(apps)
