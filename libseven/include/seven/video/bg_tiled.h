/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>
#include <seven/video/memory.h>

_LIBSEVEN_EXTERN_C

enum Tile
{
    #define BF_TILE_NUMBER_OFF 0
    #define BF_TILE_NUMBER_LEN 10

    #define TILE_NUMBER(n) BITFIELD(TILE_NUMBER, (n))

    TILE_FLIP_H = BIT(10),
    TILE_FLIP_V = BIT(11),

    #define BF_TILE_PALETTE_OFF 12
    #define BF_TILE_PALETTE_LEN 4

    #define TILE_PALETTE(n) BITFIELD(TILE_PALETTE, (n))
};

_LIBSEVEN_EXTERN_C_END
