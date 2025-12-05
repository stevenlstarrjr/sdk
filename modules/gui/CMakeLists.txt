cmake_minimum_required(VERSION 3.20)

# Hultrix GUI SDK - Wayland client wrapper
project(hultrix_gui LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Resolve repo root to locate thirdparty
get_filename_component(HULTRIX_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE)
set(THIRDPARTY_DIR "${HULTRIX_ROOT}/thirdparty")
set(THIRDPARTY_INCLUDE_DIR "${THIRDPARTY_DIR}/include")
set(THIRDPARTY_LIB_DIR "${THIRDPARTY_DIR}/lib64")

if(NOT EXISTS "${THIRDPARTY_DIR}")
    message(FATAL_ERROR "THIRDPARTY_DIR does not exist: ${THIRDPARTY_DIR}")
endif()

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(WAYLAND_CLIENT REQUIRED wayland-client)
pkg_check_modules(WAYLAND_CURSOR REQUIRED wayland-cursor)
pkg_check_modules(XKB REQUIRED xkbcommon)

# Find Yoga layout library
find_library(YOGA_LIB yogacore PATHS ${THIRDPARTY_LIB_DIR} REQUIRED NO_DEFAULT_PATH)

if(NOT YOGA_LIB)
    message(FATAL_ERROR "Yoga layout library not found in ${THIRDPARTY_LIB_DIR}")
endif()

message(STATUS "Found Yoga: ${YOGA_LIB}")

# Make graphics2d (HPainter, HImage, etc.) available for client-side rendering,
# but only if it hasn't already been added by a parent CMake.
if(NOT TARGET graphics2d)
    add_subdirectory(${HULTRIX_ROOT}/modules/graphics2d ${CMAKE_BINARY_DIR}/graphics2d_from_gui)
endif()

# Get wayland-protocols directory
execute_process(
    COMMAND ${PKG_CONFIG_EXECUTABLE} --variable=pkgdatadir wayland-protocols
    OUTPUT_VARIABLE WAYLAND_PROTOCOLS_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)

if(NOT WAYLAND_PROTOCOLS_DIR)
    set(WAYLAND_PROTOCOLS_SEARCH_PATHS
        /usr/share/wayland-protocols
        /usr/local/share/wayland-protocols
    )
    foreach(path ${WAYLAND_PROTOCOLS_SEARCH_PATHS})
        if(EXISTS "${path}/stable/xdg-shell/xdg-shell.xml")
            set(WAYLAND_PROTOCOLS_DIR ${path})
            break()
        endif()
    endforeach()
endif()

if(NOT WAYLAND_PROTOCOLS_DIR)
    message(FATAL_ERROR "Could not find wayland-protocols directory")
endif()

message(STATUS "Found wayland-protocols: ${WAYLAND_PROTOCOLS_DIR}")

# Generate xdg-shell protocol files
set(XDG_SHELL_PROTOCOL "${WAYLAND_PROTOCOLS_DIR}/stable/xdg-shell/xdg-shell.xml")
set(XDG_SHELL_HEADER "${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-client-protocol.h")
set(XDG_SHELL_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-protocol.c")

# Generate cursor-shape-v1 protocol files (for resize cursors)
set(CURSOR_SHAPE_PROTOCOL "${WAYLAND_PROTOCOLS_DIR}/staging/cursor-shape/cursor-shape-v1.xml")
set(CURSOR_SHAPE_HEADER "${CMAKE_CURRENT_BINARY_DIR}/cursor-shape-v1-client-protocol.h")
set(CURSOR_SHAPE_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/cursor-shape-v1-protocol.c")

find_program(WAYLAND_SCANNER wayland-scanner REQUIRED)

add_custom_command(
    OUTPUT ${XDG_SHELL_HEADER}
    COMMAND ${WAYLAND_SCANNER} client-header ${XDG_SHELL_PROTOCOL} ${XDG_SHELL_HEADER}
    DEPENDS ${XDG_SHELL_PROTOCOL}
    COMMENT "Generating xdg-shell client header"
)

add_custom_command(
    OUTPUT ${XDG_SHELL_SOURCE}
    COMMAND ${WAYLAND_SCANNER} private-code ${XDG_SHELL_PROTOCOL} ${XDG_SHELL_SOURCE}
    DEPENDS ${XDG_SHELL_PROTOCOL}
    COMMENT "Generating xdg-shell protocol code"
)

add_custom_command(
    OUTPUT ${CURSOR_SHAPE_HEADER}
    COMMAND ${WAYLAND_SCANNER} client-header ${CURSOR_SHAPE_PROTOCOL} ${CURSOR_SHAPE_HEADER}
    DEPENDS ${CURSOR_SHAPE_PROTOCOL}
    COMMENT "Generating cursor-shape-v1 client header"
)

add_custom_command(
    OUTPUT ${CURSOR_SHAPE_SOURCE}
    COMMAND ${WAYLAND_SCANNER} private-code ${CURSOR_SHAPE_PROTOCOL} ${CURSOR_SHAPE_SOURCE}
    DEPENDS ${CURSOR_SHAPE_PROTOCOL}
    COMMENT "Generating cursor-shape-v1 protocol code"
)

# Create library
add_library(hultrix_gui
    src/HApplication.cpp
    src/HWindow.cpp
    src/HKeyboard.cpp
    src/HShmBuffer.cpp
    src/cursor_shape_stubs.c
    ${XDG_SHELL_SOURCE}
    ${XDG_SHELL_HEADER}
    ${CURSOR_SHAPE_SOURCE}
    ${CURSOR_SHAPE_HEADER}
    # Base object system
    src/HObject.cpp
    # Layout classes and primitives (Yoga-based flexbox)
    src/HItem.cpp
    src/HLayout.cpp
    src/HBoxLayout.cpp
    # QML-style visual primitives
    src/HRectangle.cpp
    src/HText.cpp
    src/HImageItem.cpp
    src/HMouseArea.cpp
)

target_include_directories(hultrix_gui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/private
        ${CMAKE_CURRENT_BINARY_DIR}
        ${THIRDPARTY_INCLUDE_DIR}
        ${HULTRIX_ROOT}/modules/graphics2d/include
        ${WAYLAND_CLIENT_INCLUDE_DIRS}
        ${WAYLAND_CURSOR_INCLUDE_DIRS}
        ${XKB_INCLUDE_DIRS}
)

target_link_libraries(hultrix_gui
    PUBLIC
        graphics2d
        ${YOGA_LIB}
        ${WAYLAND_CLIENT_LIBRARIES}
        ${WAYLAND_CURSOR_LIBRARIES}
        ${XKB_LIBRARIES}
        pthread
)

# Example: basic window using HApplication + HWindow
add_executable(gui_basic_window example/basic_window.cpp)
target_link_libraries(gui_basic_window PRIVATE hultrix_gui)

