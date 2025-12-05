cmake_minimum_required(VERSION 3.20)

project(Hultrix LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build core Hultrix modules:
#  - modules/graphics2d  (Skia-based 2D wrapper, Ht::HGraphics2D)
#  - modules/gui         (Wayland GUI SDK, Ht::HGui)
#  - modules/compositor  (wlroots compositor SDK; no standalone target wired here yet)

add_subdirectory(modules/graphics2d)
add_subdirectory(modules/gui)
add_subdirectory(modules/compositor)
