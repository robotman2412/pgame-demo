
# SPDX-License-Identifier: CC0
# SPDX-CopyRightText: 2025 Julian Scheffers

cmake_minimum_required(VERSION 3.15.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

include(sdk/CMakeLists.txt)

project(badge_elf_app C)

add_library(main SHARED
    src/main.c
)

add_subdirectory(pgame)
target_link_libraries(main PUBLIC pgame)
