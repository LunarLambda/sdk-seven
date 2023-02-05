/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef _LIBSEVEN_HW_VIDEO_TYPES_H
#define _LIBSEVEN_HW_VIDEO_TYPES_H

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

typedef u16 Color;
typedef Color Palette[256];
typedef Color PaletteBank[16];

typedef u16 MapEntry;
typedef u8 AffineMapEntry;

struct Matrix
{
    i16 hdx; // horizontal scaling factor
    i16 vdx; // vertical shearing factor
    i16 hdy; // horizontal shearing factor
    i16 vdy; // vertical scaling factor
} _LIBSEVEN_ALIGN4;

struct Object
{
    u16 attr0;
    u16 attr1;
    u16 attr2;
    u16 _reserved;
} _LIBSEVEN_ALIGN4;

_LIBSEVEN_EXTERN_C_END

#endif /* !_LIBSEVEN_HW_VIDEO_TYPES_H */
