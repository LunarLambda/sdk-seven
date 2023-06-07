/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
    #define _LIBSEVEN_EXTERN_C extern "C" {
    #define _LIBSEVEN_EXTERN_C_END }
#else
    #define _LIBSEVEN_EXTERN_C
    #define _LIBSEVEN_EXTERN_C_END
#endif

#define _LIBSEVEN_STR(s) #s
#define _LIBSEVEN_STR2(s) _LIBSEVEN_STR(s)

#define _LIBSEVEN_ARM_FN __attribute__((__target__("arm"))) _LIBSEVEN_NOINLINE
#define _LIBSEVEN_NOINLINE __attribute__((__noinline__))
#define _LIBSEVEN_NORETURN __attribute__((__noreturn__))
#define _LIBSEVEN_ALIGN4 __attribute__((__aligned__(4)))

#define LIBSEVEN_VERSION_MAJOR 0
#define LIBSEVEN_VERSION_MINOR 18
#define LIBSEVEN_VERSION_PATCH 0

#define LIBSEVEN_VERSION \
    _LIBSEVEN_STR2(LIBSEVEN_VERSION_MAJOR) "." \
    _LIBSEVEN_STR2(LIBSEVEN_VERSION_MINOR) "." \
    _LIBSEVEN_STR2(LIBSEVEN_VERSION_PATCH)

#define VOLADDR(addr, type)             (*(type volatile (*))(addr))
#define VOLARRAY(addr, type, size)      (*(type volatile (*)[size])(addr))

#define MEMADDR(addr, type)             (*(type (*))(addr))
#define MEMARRAY(addr, type, size)      (*(type (*)[size])(addr))

#define BIT(n)                          (1 << (n))
#define BITS(n)                         (BIT(n) - 1)
#define BITFIELD(name, value)           \
    (((value) & BITS(BF_##name##_LENGTH)) << (BF_##name##_OFFSET))
