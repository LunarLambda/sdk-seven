/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

#define ALIGN(n)          __attribute__((__aligned__(n)))
#define ARM_CODE          __attribute__((__target__("arm"))) NOINLINE
#define NOINLINE          __attribute__((__noinline__))
#define NORETURN          __attribute__((__noreturn__))
#define SECTION(name)     __attribute__((__section__(name)))
#define THUMB_CODE        __attribute__((__target__("thumb"))) NOINLINE

#define IWRAM_CODE        SECTION(".iwram.text." _LIBSEVEN_COUNTER) NOINLINE
#define IWRAM_DATA        SECTION(".iwram.data." _LIBSEVEN_COUNTER)

#define EWRAM_CODE        SECTION(".ewram.text." _LIBSEVEN_COUNTER) NOINLINE
#define EWRAM_DATA        SECTION(".ewram.data." _LIBSEVEN_COUNTER)

#ifdef LIBSEVEN_COMPATIBLE
    #define IWRAM_BSS     SECTION(".bss." _LIBSEVEN_COUNTER)
    #define EWRAM_BSS     SECTION(".sbss." _LIBSEVEN_COUNTER)
#else
    #define IWRAM_BSS     SECTION(".iwram_bss." _LIBSEVEN_COUNTER)
    #define EWRAM_BSS     SECTION(".ewram_bss." _LIBSEVEN_COUNTER)
#endif /* LIBSEVEN_COMPATIBLE */
