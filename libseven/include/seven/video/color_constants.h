/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>
#include <seven/video/color.h>

_LIBSEVEN_EXTERN_C

enum ColorConstants
{
    COLOR_RED            = RGB5(31,  0,  0),
    COLOR_RED_ORANGE     = RGB5(31,  8,  0),
    COLOR_ORANGE         = RGB5(31, 15,  0),
    COLOR_ORANGE_YELLOW  = RGB5(31, 23,  0),
    COLOR_YELLOW         = RGB5(31, 31,  0),
    COLOR_YELLOW_LIME    = RGB5(23, 31,  0),
    COLOR_LIME           = RGB5(15, 31,  0),
    COLOR_LIME_GREEN     = RGB5( 8, 31,  0),
    COLOR_GREEN          = RGB5( 0, 31,  0),
    COLOR_GREEN_MINT     = RGB5( 0, 31,  8),
    COLOR_MINT           = RGB5( 0, 31, 15),
    COLOR_MINT_CYAN      = RGB5( 0, 31, 23),
    COLOR_CYAN           = RGB5( 0, 31, 31),
    COLOR_CYAN_SKYBLUE   = RGB5( 0, 23, 31),
    COLOR_SKYBLUE        = RGB5( 0, 15, 31),
    COLOR_SKYBLUE_BLUE   = RGB5( 0,  8, 31),
    COLOR_BLUE           = RGB5( 0,  0, 31),
    COLOR_BLUE_PURPLE    = RGB5( 8,  0, 31),
    COLOR_PURPLE         = RGB5(15,  0, 31),
    COLOR_PURPLE_MAGENTA = RGB5(23,  0, 31),
    COLOR_MAGENTA        = RGB5(31,  0, 31),
    COLOR_MAGENTA_PINK   = RGB5(31,  0, 23),
    COLOR_PINK           = RGB5(31,  0, 15),
    COLOR_PINK_RED       = RGB5(31,  0,  8),

    COLOR_BLACK          = RGB5( 0,  0,  0),
    COLOR_WHITE          = RGB5(31, 31, 31),

    COLOR_GRAY_0         = RGB5( 0,  0,  0),
    COLOR_GRAY_5         = RGB5( 2,  2,  2),
    COLOR_GRAY_10        = RGB5( 3,  3,  3),
    COLOR_GRAY_15        = RGB5( 5,  5,  5),
    COLOR_GRAY_20        = RGB5( 6,  6,  6),
    COLOR_GRAY_25        = RGB5( 8,  8,  8),
    COLOR_GRAY_30        = RGB5( 9,  9,  9),
    COLOR_GRAY_35        = RGB5(11, 11, 11),
    COLOR_GRAY_40        = RGB5(12, 12, 12),
    COLOR_GRAY_45        = RGB5(14, 14, 14),
    COLOR_GRAY_50        = RGB5(15, 15, 15),
    COLOR_GRAY_55        = RGB5(17, 17, 17),
    COLOR_GRAY_60        = RGB5(19, 19, 19),
    COLOR_GRAY_65        = RGB5(20, 20, 20),
    COLOR_GRAY_70        = RGB5(22, 22, 22),
    COLOR_GRAY_75        = RGB5(23, 23, 23),
    COLOR_GRAY_80        = RGB5(25, 25, 25),
    COLOR_GRAY_85        = RGB5(26, 26, 26),
    COLOR_GRAY_90        = RGB5(28, 28, 28),
    COLOR_GRAY_95        = RGB5(29, 29, 29),
    COLOR_GRAY_100       = RGB5(31, 31, 31),
};

_LIBSEVEN_EXTERN_C_END
