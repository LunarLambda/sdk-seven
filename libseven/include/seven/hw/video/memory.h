/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef _LIBSEVEN_HW_VIDEO_MEMORY_H
#define _LIBSEVEN_HW_VIDEO_MEMORY_H

#include <seven/base.h>
#include <seven/hw/memory.h>
#include <seven/hw/video/types.h>

_LIBSEVEN_EXTERN_C

#define BG_PALETTE       MEMADDR(MEM_PALETTE, Palette)
#define OBJ_PALETTE      MEMADDR(MEM_PALETTE + 512, Palette)

#define BG_PALETTE_BANK  MEMARRAY(MEM_PALETTE, PaletteBank, 16)
#define OBJ_PALETTE_BANK MEMARRAY(MEM_PALETTE + 512, PaletteBank, 16)

#define GFX_BASE_ADDR(n) (MEM_VRAM + ((n) << 14))
#define MAP_BASE_ADDR(n) (MEM_VRAM + ((n) << 11))

#define OAM_OBJS         MEMARRAY(MEM_OAM, struct Object, 128)

_LIBSEVEN_EXTERN_C_END

#endif /* !_LIBSEVEN_HW_VIDEO_MEMORY_H */
