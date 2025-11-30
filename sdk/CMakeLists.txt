
# SPDX-License-Identifier: CC0
# SPDX-CopyRightText: 2025 Julian Scheffers

set(CMAKE_C_COMPILER riscv32-esp-elf-cc)
set(CMAKE_CXX_COMPILER riscv32-esp-elf-c++)

add_compile_options(-march=rv32imafc_zicsr_zifencei -mabi=ilp32f -fPIC -mno-relax)
add_link_options(-nostartfiles -Wl,-emain)
link_libraries(-L${CMAKE_CURRENT_LIST_DIR} -lbadge -lc -lpax-gfx -lpthread -lgcc -lm -lpax-codecs)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/pax-gfx/include)
