/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

// DMA RAM  ROM  Transfer limit
//  0  R/W   -   16K
//  1  R/W   R   16K
//  2  R/W   R   16K
//  3  R/W  R/W  64K

#define REG_DMA0SRC     VOLADDR(0x040000B0, const void *)
#define REG_DMA0DST     VOLADDR(0x040000B4, void *)
#define REG_DMA0LEN     VOLADDR(0x040000B8, uint16_t)
#define REG_DMA0CNT     VOLADDR(0x040000BA, uint16_t)

#define REG_DMA1SRC     VOLADDR(0x040000BC, const void *)
#define REG_DMA1DST     VOLADDR(0x040000C0, void *)
#define REG_DMA1LEN     VOLADDR(0x040000C4, uint16_t)
#define REG_DMA1CNT     VOLADDR(0x040000C6, uint16_t)

#define REG_DMA2SRC     VOLADDR(0x040000C8, const void *)
#define REG_DMA2DST     VOLADDR(0x040000CC, void *)
#define REG_DMA2LEN     VOLADDR(0x040000D0, uint16_t)
#define REG_DMA2CNT     VOLADDR(0x040000D2, uint16_t)

#define REG_DMA3SRC     VOLADDR(0x040000D4, const void *)
#define REG_DMA3DST     VOLADDR(0x040000D8, void *)
#define REG_DMA3LEN     VOLADDR(0x040000DC, uint16_t)
#define REG_DMA3CNT     VOLADDR(0x040000DE, uint16_t)

struct DMA
{
    const void *src;
    void *dst;
    uint16_t len;
    uint16_t cnt;
};

enum DMAControl
{
    #define BF_DMA_DST_OFF 5
    #define BF_DMA_DST_LEN 2

    #define DMA_DST(n) BITFIELD(DMA_DST, (n))

    DMA_DST_INCREMENT   = DMA_DST(0),
    DMA_DST_DECREMENT   = DMA_DST(1),
    DMA_DST_FIXED       = DMA_DST(2),
    DMA_DST_RELOAD      = DMA_DST(3),

    #define BF_DMA_SRC_OFF 7
    #define BF_DMA_SRC_LEN 2

    #define DMA_SRC(n) BITFIELD(DMA_SRC, (n))

    DMA_SRC_INCREMENT   = DMA_SRC(0),
    DMA_SRC_DECREMENT   = DMA_SRC(1),
    DMA_SRC_FIXED       = DMA_SRC(2),

    DMA_REPEAT          = BIT(9),

    DMA_32BIT           = BIT(10),
    DMA_16BIT           = !DMA_32BIT,

    #define BF_DMA_START_OFF 12
    #define BF_DMA_START_LEN 2

    #define DMA_START(n) BITFIELD(DMA_START, (n))

    DMA_START_NOW       = DMA_START(0),
    DMA_START_HBLANK    = DMA_START(1),
    DMA_START_VBLANK    = DMA_START(2),

    // DMA1, DMA2
    DMA_START_SOUND     = DMA_START(3),
    // DMA3
    DMA_START_CAPTURE   = DMA_START(3),

    // On transfer completion
    DMA_IRQ_ENABLE      = BIT(14),
    DMA_ENABLE          = BIT(15),
};

enum DMAControlPreset
{
    DMA_PRESET_COPY16   = DMA_16BIT,
    DMA_PRESET_COPY32   = DMA_32BIT,
    DMA_PRESET_FILL16   = DMA_16BIT | DMA_SRC_FIXED,
    DMA_PRESET_FILL32   = DMA_32BIT | DMA_SRC_FIXED,
    DMA_PRESET_HBLANK   = DMA_REPEAT | DMA_START_HBLANK,
    DMA_PRESET_VBLANK   = DMA_REPEAT | DMA_START_VBLANK,
    DMA_PRESET_SOUND    = DMA_REPEAT | DMA_START_SOUND,
    DMA_PRESET_CAPTURE  = DMA_REPEAT | DMA_START_CAPTURE,
};

#define DMA_LEN(len, flags) \
    ((flags) & DMA_32BIT ? (len) >> 2 : (len) >> 1)

#define DMA_BUILD(src, dst, len, flags) \
    ((struct DMA){ src, dst, DMA_LEN(len, flags), flags })

extern void dmaSet(uint32_t channel, struct DMA dma);

_LIBSEVEN_EXTERN_C_END
