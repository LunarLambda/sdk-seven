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
    i32 quot;
    i32 rem;
};

extern i32 biosDiv(i32 numerator, i32 denominator);
extern struct Div biosDivMod(i32 numerator, i32 denominator);
extern u16 biosSqrt(u32 x);
extern i16 biosArcTan(i16 tan);
extern u16 biosArcTan2(i16 x, i16 y);

_LIBSEVEN_EXTERN_C_END

#endif /* !_LIBSEVEN_HW_BIOS_MATH_H */
