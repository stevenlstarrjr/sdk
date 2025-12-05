cmake_minimum_required(VERSION 3.16)

project(math2d
    VERSION 0.1.0
    DESCRIPTION "math2d - 2D math library for graphics"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(math2d
    src/HVector2.cpp
    src/HMatrix3x3.cpp
    src/HTransform2D.cpp)

target_include_directories(math2d
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(math2d_tests
    tests/main.cpp)

target_link_libraries(math2d_tests
    PRIVATE
        math2d)
