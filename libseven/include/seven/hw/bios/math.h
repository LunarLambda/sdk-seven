/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef _LIBSEVEN_HW_BIOS_MATH_H
#define _LIBSEVEN_HW_BIOS_MATH_H

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

struct Div
{
    int32_t quot;
    int32_t rem;
};

extern int32_t biosDiv(int32_t numerator, int32_t denominator);
extern struct Div biosDivMod(int32_t numerator, int32_t denominator);
extern uint16_t biosSqrt(uint32_t x);
extern int16_t biosArcTan(int16_t tan);
extern uint16_t biosArcTan2(int16_t x, int16_t y);

_LIBSEVEN_EXTERN_C_END

#endif /* !_LIBSEVEN_HW_BIOS_MATH_H */
