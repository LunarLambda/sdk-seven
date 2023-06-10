/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

#define REG_DISPCNT  VOLADDR(0x04000000, uint16_t)
#define REG_DISPSTAT VOLADDR(0x04000004, uint16_t)
#define REG_VCOUNT   VOLADDR(0x04000006, const uint16_t)
#define REG_BGCNT    VOLARRAY(0x04000008, uint16_t, 4)
#define REG_BG0CNT   VOLADDR(0x04000008, uint16_t)
#define REG_BG1CNT   VOLADDR(0x0400000A, uint16_t)
#define REG_BG2CNT   VOLADDR(0x0400000C, uint16_t)
#define REG_BG3CNT   VOLADDR(0x0400000E, uint16_t)

enum LCDDimensions
{
    LCD_WIDTH     = 240,
    LCD_HEIGHT    = 160,
    LCD_SCANLINES = 228,
};

enum DisplayControl
{
    #define BF_DISPLAY_MODE_OFF 0
    #define BF_DISPLAY_MODE_LEN 3

    #define DISPLAY_MODE(n) BITFIELD(DISPLAY_MODE, (n))

    DISPLAY_MODE_REGULAR        = DISPLAY_MODE(0),
    DISPLAY_MODE_MIXED          = DISPLAY_MODE(1),
    DISPLAY_MODE_AFFINE         = DISPLAY_MODE(2),
    DISPLAY_MODE_BITMAP         = DISPLAY_MODE(3),
    DISPLAY_MODE_BITMAP_INDEXED = DISPLAY_MODE(4),
    DISPLAY_MODE_BITMAP_SMALL   = DISPLAY_MODE(5),

    DISPLAY_FRAME_SELECT        = BIT(4),

    DISPLAY_OBJ_LAYOUT_1D       = BIT(6),
    DISPLAY_OBJ_LAYOUT_2D       = !DISPLAY_OBJ_LAYOUT_1D,

    DISPLAY_FORCE_BLANK         = BIT(7),

    DISPLAY_BG0_ENABLE          = BIT(8),
    DISPLAY_BG1_ENABLE          = BIT(9),
    DISPLAY_BG2_ENABLE          = BIT(10),
    DISPLAY_BG3_ENABLE          = BIT(11),
    DISPLAY_OBJ_ENABLE          = BIT(12),
    DISPLAY_WIN0_ENABLE         = BIT(13),
    DISPLAY_WIN1_ENABLE         = BIT(14),
    DISPLAY_OBJ_WIN_ENABLE      = BIT(15),
};

enum DisplayStatus
{
    LCD_IN_VBLANK         = BIT(0),
    LCD_IN_HBLANK         = BIT(1),
    LCD_VCOUNT_MATCH      = BIT(2),

    LCD_VBLANK_IRQ_ENABLE = BIT(3),
    LCD_HBLANK_IRQ_ENABLE = BIT(4),
    LCD_VCOUNT_IRQ_ENABLE = BIT(5),

    #define BF_LCD_TARGET_VCOUNT_OFF 8
    #define BF_LCD_TARGET_VCOUNT_LEN 8

    #define LCD_TARGET_VCOUNT(n) BITFIELD(LCD_TARGET_VCOUNT, (n))
};

enum VerticalCount
{
    VCOUNT_DRAW_START    = 0,
    VCOUNT_DRAW_END      = 160,
    VCOUNT_BLANK_START   = 160,
    VCOUNT_BLANK_END     = 0,
};

enum BackgroundControl
{
    #define BF_BG_PRIORITY_OFF 0
    #define BF_BG_PRIORITY_LEN 2

    #define BG_PRIORITY(n) BITFIELD(BG_PRIORITY, (n))

    BG_PRIORITY_MIN          = BG_PRIORITY(3),
    BG_PRIORITY_MAX          = BG_PRIORITY(0),

    #define BF_BG_GFX_BASE_OFF 2
    #define BF_BG_GFX_BASE_LEN 2

    #define BG_GFX_BASE(n) BITFIELD(BG_GFX_BASE, (n))

    BG_MOSAIC_ENABLE         = BIT(6),

    BG_TILE_8BPP             = BIT(7),
    BG_TILE_4BPP             = !BG_TILE_8BPP,

    #define BF_BG_MAP_BASE_OFF 8
    #define BF_BG_MAP_BASE_LEN 5

    #define BG_MAP_BASE(n) BITFIELD(BG_MAP_BASE, (n))

    BG_AFFINE_WRAP           = BIT(13),

    #define BF_BG_SIZE_OFF 14
    #define BF_BG_SIZE_LEN 2

    #define BG_SIZE(n) BITFIELD(BG_SIZE, (n))

    BG_SIZE_256X256          = BG_SIZE(0),
    BG_SIZE_512X256          = BG_SIZE(1),
    BG_SIZE_256X512          = BG_SIZE(2),
    BG_SIZE_512X512          = BG_SIZE(3),

    #define BF_BG_AFFINE_SIZE_OFF 14
    #define BF_BG_AFFINE_SIZE_LEN 2

    #define BG_AFFINE_SIZE(n) BITFIELD(BG_AFFINE_SIZE, (n))

    BG_AFFINE_SIZE_128X128   = BG_AFFINE_SIZE(0),
    BG_AFFINE_SIZE_256X256   = BG_AFFINE_SIZE(1),
    BG_AFFINE_SIZE_512X512   = BG_AFFINE_SIZE(2),
    BG_AFFINE_SIZE_1024X1024 = BG_AFFINE_SIZE(3),
};

_LIBSEVEN_EXTERN_C_END
