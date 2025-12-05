cmake_minimum_required(VERSION 3.20)

project(graphics2d
    VERSION 0.1.0
    DESCRIPTION "graphics2d "
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Resolve thirdparty root (default to repo-level thirdparty)
get_filename_component(HULTRIX_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE)
set(THIRDPARTY_DIR "${HULTRIX_ROOT}/thirdparty" CACHE PATH "Path to Hultrix thirdparty directory")

if(NOT EXISTS "${THIRDPARTY_DIR}")
    message(FATAL_ERROR "THIRDPARTY_DIR does not exist: ${THIRDPARTY_DIR}")
endif()

set(THIRDPARTY_INCLUDE_DIR "${THIRDPARTY_DIR}/include")
set(THIRDPARTY_LIB_DIR "${THIRDPARTY_DIR}/lib64")

if(NOT EXISTS "${THIRDPARTY_INCLUDE_DIR}")
    message(FATAL_ERROR "Thirdparty include dir not found: ${THIRDPARTY_INCLUDE_DIR}")
endif()
if(NOT EXISTS "${THIRDPARTY_LIB_DIR}")
    message(FATAL_ERROR "Thirdparty lib dir not found: ${THIRDPARTY_LIB_DIR}")
endif()

file(GLOB_RECURSE GRAPHICS2D_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Exclude window/front-end code: we only want the Skia wrapper
list(FILTER GRAPHICS2D_SOURCES EXCLUDE REGEX ".*/HWindow(Base)?\\.cpp$")
list(FILTER GRAPHICS2D_SOURCES EXCLUDE REGEX ".*/HRenderWindow\\.cpp$")

add_library(graphics2d ${GRAPHICS2D_SOURCES})

target_include_directories(graphics2d
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${THIRDPARTY_INCLUDE_DIR}
        ${THIRDPARTY_INCLUDE_DIR}/skia
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/private)

find_package(Vulkan REQUIRED)
find_package(PNG REQUIRED)
find_package(JPEG REQUIRED)
find_package(ZLIB REQUIRED)

# WebP (decoder + demux) for Skia image codecs
find_library(WEBP_LIB webp)
find_library(WEBP_DEMUX_LIB webpdemux)

if(NOT WEBP_LIB OR NOT WEBP_DEMUX_LIB)
    message(FATAL_ERROR "Required WebP libraries (webp, webpdemux) not found on the system")
endif()

# Find Skia library explicitly
find_library(SKIA_LIB skia PATHS ${THIRDPARTY_LIB_DIR} REQUIRED NO_DEFAULT_PATH)

if(NOT SKIA_LIB)
    message(FATAL_ERROR "Skia library not found in ${THIRDPARTY_LIB_DIR}")
endif()

target_link_libraries(graphics2d
    PUBLIC
        ${SKIA_LIB}
        Vulkan::Vulkan
        PNG::PNG
        JPEG::JPEG
        ZLIB::ZLIB
        ${WEBP_LIB}
        ${WEBP_DEMUX_LIB}
        pthread
        dl
        fontconfig
        freetype)

# Build examples
option(BUILD_GRAPHICS2D_EXAMPLES "Build graphics2d examples" ON)

if(BUILD_GRAPHICS2D_EXAMPLES)
    # Basic shapes example
    add_executable(basic_shapes examples/basic_shapes.cpp)
    target_link_libraries(basic_shapes PUBLIC graphics2d)

    # Text rendering example
    add_executable(text_rendering examples/text_rendering.cpp)
    target_link_libraries(text_rendering PUBLIC graphics2d)

    # Paths and boolean operations example
    add_executable(paths_example examples/paths_example.cpp)
    target_link_libraries(paths_example PUBLIC graphics2d)

    # Gradients example
    add_executable(gradients_example examples/gradients_example.cpp)
    target_link_libraries(gradients_example PUBLIC graphics2d)

    # Transforms example
    add_executable(transforms_example examples/transforms_example.cpp)
    target_link_libraries(transforms_example PUBLIC graphics2d)

    # Picture recording/replay example
    add_executable(picture_example examples/picture_example.cpp)
    target_link_libraries(picture_example PUBLIC graphics2d)

    # Paint device example
    add_executable(paintdevice_example examples/paintdevice_example.cpp)
    target_link_libraries(paintdevice_example PUBLIC graphics2d)

    # Create output directory for examples
    add_custom_command(TARGET basic_shapes POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:basic_shapes>/output
        COMMENT "Creating output directory for examples")
    add_custom_command(TARGET text_rendering POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:text_rendering>/output
        COMMENT "Creating output directory for examples")
    add_custom_command(TARGET paths_example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:paths_example>/output
        COMMENT "Creating output directory for examples")
    add_custom_command(TARGET gradients_example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:gradients_example>/output
        COMMENT "Creating output directory for examples")
    add_custom_command(TARGET transforms_example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:transforms_example>/output
        COMMENT "Creating output directory for examples")
    add_custom_command(TARGET picture_example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:picture_example>/output
        COMMENT "Creating output directory for examples")
    add_custom_command(TARGET paintdevice_example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:paintdevice_example>/output
        COMMENT "Creating output directory for examples")
endif()
