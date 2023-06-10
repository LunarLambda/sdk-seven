/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>
#include <seven/hw/bios.h>

_LIBSEVEN_EXTERN_C

struct Div
{
    int32_t quot;
    int32_t rem;
};

inline int32_t biosDiv(int32_t numerator, int32_t denominator)
{
    register int32_t r0 __asm__("r0") = numerator;
    register int32_t r1 __asm__("r1") = denominator;

    __asm__(_LIBSEVEN_INLINE_SWI
            : "+r"(r0), "+r"(r1)
            : [num]"I"(SWI_DIV)
            : "r3");

    return r0;
}

extern struct Div biosDivMod(int32_t numerator, int32_t denominator);

inline uint32_t biosSqrt(uint32_t x)
{
    register uint32_t r0 __asm__("r0") = x;

    __asm__(_LIBSEVEN_INLINE_SWI
            : "+r"(r0)
            : [num]"I"(SWI_SQRT)
            : "r1", "r3");

    return r0;
}

inline int16_t biosArcTan(int16_t tan)
{
    register int16_t r0 __asm__("r0") = tan;

    __asm__(_LIBSEVEN_INLINE_SWI
            : "+r"(r0)
            : [num]"I"(SWI_ARCTAN)
            : "r1", "r3");

    return r0;
}

inline uint16_t biosArcTan2(int16_t x, int16_t y)
{
    register uint16_t r0 __asm__("r0") = x;
    register uint16_t r1 __asm__("r1") = y;

    __asm__(_LIBSEVEN_INLINE_SWI
            : "+r"(r0), "+r"(r1)
            : [num]"I"(SWI_ARCTAN2)
            : "r3");

    return r0;
}

_LIBSEVEN_EXTERN_C_END
