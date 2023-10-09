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

#define _LIBSEVEN_STR(s)     #s
#define _LIBSEVEN_STR1(s)    _LIBSEVEN_STR(s)

#define _LIBSEVEN_COUNTER    _LIBSEVEN_STR1(__COUNTER__)

#define _LIBSEVEN_ALIGNED    __attribute__((__aligned__(4)))
#define _LIBSEVEN_NOINLINE   __attribute__((__noinline__))
#define _LIBSEVEN_NORETURN   __attribute__((__noreturn__))
#define _LIBSEVEN_TARGET_ARM __attribute__((__target__("arm"), __noinline__))

#define LIBSEVEN_VERSION_MAJOR 0
#define LIBSEVEN_VERSION_MINOR 22
#define LIBSEVEN_VERSION_PATCH 2

#define LIBSEVEN_VERSION \
    _LIBSEVEN_STR1(LIBSEVEN_VERSION_MAJOR) "." \
    _LIBSEVEN_STR1(LIBSEVEN_VERSION_MINOR) "." \
    _LIBSEVEN_STR1(LIBSEVEN_VERSION_PATCH)

#define VOLADDR(addr, type)        (*(type volatile (*))(addr))
#define VOLARRAY(addr, type, size) (*(type volatile (*)[size])(addr))

#define MEMADDR(addr, type)        (*(type (*))(addr))
#define MEMARRAY(addr, type, size) (*(type (*)[size])(addr))

#define BIT(n)            (1 << (n))
#define BITS(n)           (BIT(n) - 1)
#define BITFIELD(name, x) (((x) & BITS(BF_##name##_LEN)) << (BF_##name##_OFF))

#define UNIT_KIB(n)        ((size_t)(n) << 10)
#define UNIT_MIB(n)        ((size_t)(n) << 20)
