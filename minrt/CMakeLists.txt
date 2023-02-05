#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
#

cmake_minimum_required(VERSION 3.0)

project(minrt C ASM)
set(CMAKE_INCLUDE_FLAG_ASM "-Wa,-I")

add_library(minrt STATIC
    src/gba/crt0.s
    src/gba/exit.c
    src/gba/fini.c
    src/gba/init.c
    src/gba/ram.c
    src/gba/rom_header.s
)

target_include_directories(minrt PUBLIC include/)
target_include_directories(minrt PRIVATE src/gba/)

target_compile_options(minrt PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-Os -g3 -gdwarf-4 -ffunction-sections -fdata-sections -std=c99 -Wall -Wpedantic -mabi=aapcs -mcpu=arm7tdmi -mthumb>
)

target_link_options(minrt INTERFACE
    -mthumb
    -specs=${CMAKE_CURRENT_LIST_DIR}/lib/nocrt0.specs
    -L${CMAKE_CURRENT_LIST_DIR}/lib/ldscripts
    -Trom.mem
    -Tgba.x
)

add_library(minrt_multiboot STATIC
    src/gba/crt0.s
    src/gba/exit.c
    src/gba/fini.c
    src/gba/init.c
    src/gba/ram.c
    src/gba/multiboot_header.s
)

target_include_directories(minrt_multiboot PUBLIC include/)
target_include_directories(minrt_multiboot PRIVATE src/gba/)

target_compile_options(minrt_multiboot PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-Os -g3 -gdwarf-4 -ffunction-sections -fdata-sections -std=c99 -Wall -Wpedantic -mabi=aapcs -mcpu=arm7tdmi -mthumb>
)

target_link_options(minrt_multiboot INTERFACE
    -mthumb
    -specs=${CMAKE_CURRENT_LIST_DIR}/lib/nocrt0.specs
    -L${CMAKE_CURRENT_LIST_DIR}/lib/ldscripts
    -Tmultiboot.mem
    -Tgba.x
)

add_library(minrt_mb ALIAS minrt_multiboot)

if(EXISTS $ENV{DEVKITPRO})
    install(TARGETS minrt minrt_multiboot DESTINATION "$ENV{DEVKITPRO}/minrt/lib")
    install(DIRECTORY include/ DESTINATION "$ENV{DEVKITPRO}/minrt/include")
    install(FILES LICENSE.txt DESTINATION "$ENV{DEVKITPRO}/minrt")
endif()
