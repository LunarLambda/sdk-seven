/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef _LIBSEVEN_UTIL_BIT_H
#define _LIBSEVEN_UTIL_BIT_H

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

extern u32 bitCTZ32(u32 value);
extern u32 bitCTZ16(u16 value);
extern u32 bitCTZ8(u8 value);

extern u32 bitCLZ32(u32 value);
extern u32 bitCLZ16(u16 value);
extern u32 bitCLZ8(u8 value);

_LIBSEVEN_EXTERN_C_END

#endif /* !_LIBSEVEN_UTIL_BIT_H */

