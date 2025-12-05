cmake_minimum_required(VERSION 3.20)

# Hultrix wlroots-based compositor SDK
project(hultrix_compositor LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Resolve repo root to locate thirdparty wlroots build and headers
get_filename_component(HULTRIX_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE)
set(THIRDPARTY_DIR "${HULTRIX_ROOT}/thirdparty")
set(THIRDPARTY_INCLUDE_DIR "${THIRDPARTY_DIR}/include")
set(THIRDPARTY_LIB_DIR "${THIRDPARTY_DIR}/lib64")

# Find wlroots library
find_library(WLROOTS_LIB wlroots-0.20 PATHS ${THIRDPARTY_LIB_DIR} REQUIRED NO_DEFAULT_PATH)

if(NOT WLROOTS_LIB)
    message(FATAL_ERROR "wlroots static library not found in ${THIRDPARTY_LIB_DIR}. Expected libwlroots-0.20.a")
endif()

message(STATUS "Found wlroots: ${WLROOTS_LIB}")

# Pixman headers (wlroots depends on pixman.h)
find_path(PIXMAN_INCLUDE_DIR pixman.h
    PATH_SUFFIXES pixman-1
)

if(NOT PIXMAN_INCLUDE_DIR)
    message(FATAL_ERROR "pixman.h not found; install pixman development headers")
endif()

add_library(hultrix_compositor
    src/HWaylandCompositor.cpp
    src/HWaylandOutput.cpp
    src/HWaylandSurface.cpp
    src/HWaylandXdgShell.cpp
    src/HWaylandSeat.cpp
    src/HWaylandKeyboard.cpp
    src/HWaylandPointer.cpp
    # Add more classes as they are implemented:
    # etc.
)

target_include_directories(hultrix_compositor
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/private
        ${THIRDPARTY_INCLUDE_DIR}
        ${THIRDPARTY_INCLUDE_DIR}/wlroots
        ${THIRDPARTY_INCLUDE_DIR}/wlroots/wlroots-0.20
        ${THIRDPARTY_INCLUDE_DIR}/wlr
        ${PIXMAN_INCLUDE_DIR}
)

target_link_libraries(hultrix_compositor
    PUBLIC
        ${WLROOTS_LIB}
        xkbcommon
        wayland-server
        drm
        pixman-1
        EGL
        gbm
        GLESv2
        lcms2
        seat
        systemd
        input
        udev
        cap
        wayland-client
        m
        pthread
        rt
        ffi
)

target_compile_definitions(hultrix_compositor
    PUBLIC
        WLR_USE_UNSTABLE
)
