# Copyright 2024 HML Project Contributors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.16)
project(HML DESCRIPTION "HTML-like Markup Language Parser and Engine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find ANTLR4 runtime using CMake config
find_package(antlr4-runtime REQUIRED)

# Include directories
include_directories(/usr/include/antlr4-runtime)
include_directories(include)

# ANTLR generated sources
set(ANTLR_SOURCES
    src/HmlLexer.cpp
    src/HmlParser.cpp
    src/HmlBaseVisitor.cpp
    src/HmlVisitor.cpp
    src/HmlBaseListener.cpp
    src/HmlListener.cpp
)

# Create library from ANTLR sources
add_library(hml_parser ${ANTLR_SOURCES})
target_link_libraries(hml_parser antlr4-runtime)

# Test executable
add_executable(test_hml examples/test_hml.cpp)
target_link_libraries(test_hml hml_parser antlr4-runtime)

# Compiler flags for better error messages
target_compile_options(test_hml PRIVATE -Wall -Wextra)

