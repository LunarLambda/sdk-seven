/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>
#include <seven/hw/bios.h>

_LIBSEVEN_EXTERN_C

struct BitUnPackParam
{
    uint16_t src_length;     // in bytes
    uint8_t  src_width;      // width of each src element (1, 2, 4, 8)
    uint8_t  dst_width;      // width of each dst element (1, 2, 4, 8, 16, 32)
    uint32_t offset:31;      // value to add to each dst element
    uint32_t keep_zeroes:1;  // whether to add offset to zero elements too
};

inline void biosBitUnPack(
        const void *src,
        void *dst,
        const struct BitUnPackParam *param)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;
    register const struct BitUnPackParam *r2 __asm__("r2") = param;

    __asm__(_LIBSEVEN_INLINE_SWI
            : "+r"(r0), "+r"(r1), "+r"(r2)
            : [num]"I"(SWI_BITUNPACK)
            : "r3", "memory");
}

inline void biosLZ77UnCompWram(const void *src, void *dst)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;

    __asm__(_LIBSEVEN_INLINE_SWI
            : "+r"(r0), "+r"(r1)
            : [num]"I"(SWI_LZ77UNCOMPWRAM)
            : "r3", "memory");
}

inline void biosLZ77UnCompVram(const void *src, void *dst)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;

    __asm__(_LIBSEVEN_INLINE_SWI
            : "+r"(r0), "+r"(r1)
            : [num]"I"(SWI_LZ77UNCOMPVRAM)
            : "r3", "memory");
}

inline void biosHuffUnComp(const void *src, void *dst)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;

    __asm__(_LIBSEVEN_INLINE_SWI
            : "+r"(r0), "+r"(r1)
            : [num]"I"(SWI_HUFFUNCOMP)
            : "r3", "memory");
}

inline void biosRLUnCompWram(const void *src, void *dst)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;

    __asm__(_LIBSEVEN_INLINE_SWI
            : "+r"(r0), "+r"(r1)
            : [num]"I"(SWI_RLUNCOMPWRAM)
            : "r3", "memory");
}

inline void biosRLUnCompVram(const void *src, void *dst)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;

    __asm__(_LIBSEVEN_INLINE_SWI
            : "+r"(r0), "+r"(r1)
            : [num]"I"(SWI_RLUNCOMPVRAM)
            : "r3", "memory");
}

inline void biosDiff8bitUnFilterWram(const void *src, void *dst)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;

    __asm__(_LIBSEVEN_INLINE_SWI
            : "+r"(r0), "+r"(r1)
            : [num]"I"(SWI_DIFF8BITUNFILTERWRAM)
            : "r3", "memory");
}

inline void biosDiff8bitUnFilterVram(const void *src, void *dst)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;

    __asm__(_LIBSEVEN_INLINE_SWI
            : "+r"(r0), "+r"(r1)
            : [num]"I"(SWI_DIFF8BITUNFILTERVRAM)
            : "r3", "memory");
}

inline void biosDiff16bitUnFilter(const void *src, void *dst)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;

    __asm__(_LIBSEVEN_INLINE_SWI
            : "+r"(r0), "+r"(r1)
            : [num]"I"(SWI_DIFF16BITUNFILTER)
            : "r3", "memory");
}

_LIBSEVEN_EXTERN_C_END
