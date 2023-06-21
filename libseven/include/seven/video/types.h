/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

typedef uint16_t Color;
typedef Color Palette[256];
typedef Color PaletteBank[16];

typedef uint16_t MapEntry;
typedef uint8_t AffineMapEntry;

_LIBSEVEN_ALIGNED
struct Matrix
{
    int16_t hdx; // horizontal scaling factor
    int16_t vdx; // vertical shearing factor
    int16_t hdy; // horizontal shearing factor
    int16_t vdy; // vertical scaling factor
};

_LIBSEVEN_ALIGNED
struct Object
{
    uint16_t attr0;
    uint16_t attr1;
    uint16_t attr2;
    uint16_t _reserved;
};

_LIBSEVEN_EXTERN_C_END
