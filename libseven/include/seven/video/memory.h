/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>
#include <seven/memory.h>
#include <seven/video/types.h>

_LIBSEVEN_EXTERN_C

#define BG_PALETTE       MEMADDR(MEM_PALETTE, Palette)
#define OBJ_PALETTE      MEMADDR(MEM_PALETTE + 512, Palette)

#define BG_PALETTE_BANK  MEMARRAY(MEM_PALETTE, PaletteBank, 16)
#define OBJ_PALETTE_BANK MEMARRAY(MEM_PALETTE + 512, PaletteBank, 16)

#define GFX_BASE_ADDR(n) (MEM_VRAM + ((n) << 14))
#define MAP_BASE_ADDR(n) (MEM_VRAM + ((n) << 11))

#define OAM_OBJS         MEMARRAY(MEM_OAM, struct Object, 128)


extern int32_t vramAddrToBgTileIndex(const void *addr, uint16_t bgcnt);
extern int32_t vramAddrToObjTileIndex(const void *addr);

struct MapIndex
{
    bool ok;
    uint8_t block;
    uint8_t x;
    uint8_t y;
};

extern struct MapIndex vramAddrToMapIndex(const void *addr, uint16_t bgcnt, bool is_affine);

_LIBSEVEN_EXTERN_C_END
