/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

typedef int8_t          i8;
typedef int16_t         i16;
typedef int32_t         i32;
typedef int64_t         i64;
typedef ptrdiff_t       isize;
typedef intptr_t        iptr;

typedef uint8_t         u8;
typedef uint16_t        u16;
typedef uint32_t        u32;
typedef uint64_t        u64;
typedef size_t          usize;
typedef uintptr_t       uptr;

#define I8_MIN          INT8_MIN
#define I16_MIN         INT16_MIN
#define I32_MIN         INT32_MIN
#define I64_MIN         INT64_MIN
#define ISIZE_MIN       PTRDIFF_MIN
#define IPTR_MIN        INTPTR_MIN

#define I8_MAX          INT8_MAX
#define I16_MAX         INT16_MAX
#define I32_MAX         INT32_MAX
#define I64_MAX         INT64_MAX
#define ISIZE_MAX       PTRDIFF_MAX
#define IPTR_MAX        INTPTR_MAX

#define I8_BITS         8
#define I16_BITS        16
#define I32_BITS        32
#define I64_BITS        64
#define ISIZE_BITS      (CHAR_BIT * sizeof(isize))
#define IPTR_BITS       (CHAR_BIT * sizeof(iptr))

#define U8_MIN          0
#define U16_MIN         0
#define U32_MIN         0
#define U64_MIN         0
#define USIZE_MIN       0
#define UPTR_MIN        0

#define U8_MAX          UINT8_MAX
#define U16_MAX         UINT16_MAX
#define U32_MAX         UINT32_MAX
#define U64_MAX         UINT64_MAX
#define USIZE_MAX       SIZE_MAX
#define UPTR_MAX        UINTPTR_MAX

#define U8_BITS         8
#define U16_BITS        16
#define U32_BITS        32
#define U64_BITS        64
#define USIZE_BITS      (CHAR_BIT * sizeof(usize))
#define UPTR_BITS       (CHAR_BIT * sizeof(uptr))

#ifdef LIBSEVEN_COMPATIBLE

typedef i8              s8;
typedef i16             s16;
typedef i32             s32;
typedef i64             s64;
typedef isize           ssize;
typedef iptr            sptr;

#define S8_MIN          I8_MIN
#define S16_MIN         I16_MIN
#define S32_MIN         I32_MIN
#define S64_MIN         I64_MIN
#define SSIZE_MIN       ISIZE_MIN
#define SPTR_MIN        IPTR_MIN

#define S8_MAX          I8_MAX
#define S16_MAX         I16_MAX
#define S32_MAX         I32_MAX
#define S64_MAX         I64_MAX
#define SSIZE_MAX       ISIZE_MAX
#define SPTR_MAX        IPTR_MAX

#define S8_BITS         I8_BITS
#define S16_BITS        I16_BITS
#define S32_BITS        I32_BITS
#define S64_BITS        I64_BITS
#define SSIZE_BITS      ISIZE_BITS
#define SPTR_BITS       IPTR_BITS

#endif /* LIBSEVEN_COMPATIBLE */
