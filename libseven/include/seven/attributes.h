/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef _LIBSEVEN_ATTRIBUTES_H
#define _LIBSEVEN_ATTRIBUTES_H

#include <seven/base.h>

#define _LIBSEVEN_SECCOUNT      _LIBSEVEN_STR2(__COUNTER__)

#define PACKED                  __attribute__((__packed__))
#define ALIGN(n)                __attribute__((__aligned__(n)))
#define NORETURN                __attribute__((__noreturn__))
#define NOINLINE                __attribute__((__noinline__))
#define ARM_CODE                __attribute__((__target__("arm"))) NOINLINE
#define THUMB_CODE              __attribute__((__target__("thumb"))) NOINLINE

#define SECTION(name)           __attribute__((__section__(name)))

#define IWRAM_SECTION(suffix)   SECTION(".iwram" suffix)
#define IWRAM_OVERLAY(number)   SECTION(".iwram" #number)

#define IWRAM_CODE              IWRAM_SECTION(".text." _LIBSEVEN_SECCOUNT) NOINLINE
#define IWRAM_DATA              IWRAM_SECTION(".data." _LIBSEVEN_SECCOUNT)

#define EWRAM_SECTION(suffix)   SECTION(".ewram" suffix)
#define EWRAM_OVERLAY(number)   SECTION(".ewram" #number)

#define EWRAM_CODE              EWRAM_SECTION(".text." _LIBSEVEN_SECCOUNT) NOINLINE
#define EWRAM_DATA              EWRAM_SECTION(".data." _LIBSEVEN_SECCOUNT)

#ifndef _LIBSEVEN_NOCOMPATIBLE
    #define IWRAM_BSS           SECTION(".bss." _LIBSEVEN_SECCOUNT)
    #define EWRAM_BSS           SECTION(".sbss." _LIBSEVEN_SECCOUNT)
#else
    #define IWRAM_BSS           SECTION(".iwram_bss." _LIBSEVEN_SECCOUNT)
    #define EWRAM_BSS           SECTION(".ewram_bss." _LIBSEVEN_SECCOUNT)
#endif /* !_LIBSEVEN_NOCOMPATIBLE */

#endif /* !_LIBSEVEN_ATTRIBUTES_H */
