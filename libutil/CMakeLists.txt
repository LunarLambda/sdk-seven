#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
#

cmake_minimum_required(VERSION 3.0)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    # Default to MinSizeRel build type
    set(CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

project(libutil C ASM)
set(CMAKE_INCLUDE_FLAG_ASM "-Wa,-I")

add_library(util STATIC
    src/assert.c
    src/bit.s
    src/debug.s
    src/log.c
    src/mem.s
    src/profile.s
    src/rand.s
    src/simd.s
    src/str.s
)

target_include_directories(util PUBLIC include/)
target_include_directories(util PRIVATE src/)

target_compile_options(util PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-Os -g3 -gdwarf-4 -ffunction-sections -fdata-sections -std=c99 -Wall -Wpedantic -mabi=aapcs -mcpu=arm7tdmi -mthumb>
)

# Allow the string "libutil" as a parameter for target_link_libraries
add_library(libutil ALIAS util)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT AND EXISTS $ENV{DEVKITPRO})
    file(TO_CMAKE_PATH "$ENV{DEVKITPRO}" ENV_DEVKITPRO)
    set(CMAKE_INSTALL_PREFIX "${ENV_DEVKITPRO}/libseven" CACHE PATH "..." FORCE)
endif()

install(TARGETS util LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
