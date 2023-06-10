/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

#define REG_WIN0H   VOLADDR(0x04000040, uint16_t)
#define REG_WIN1H   VOLADDR(0x04000042, uint16_t)
#define REG_WIN0V   VOLADDR(0x04000044, uint16_t)
#define REG_WIN1V   VOLADDR(0x04000046, uint16_t)

#define REG_WIN0IN  VOLADDR(0x04000048, uint8_t)
#define REG_WIN1IN  VOLADDR(0x04000049, uint8_t)
#define REG_WIN0OUT VOLADDR(0x0400004A, uint8_t)
#define REG_WIN1OUT VOLADDR(0x0400004B, uint8_t)

enum WindowControl
{
    WINDOW_BG0_ENABLE   = BIT(0),
    WINDOW_BG1_ENABLE   = BIT(1),
    WINDOW_BG2_ENABLE   = BIT(2),
    WINDOW_BG3_ENABLE   = BIT(3),
    WINDOW_OBJ_ENABLE   = BIT(4),
    WINDOW_BLEND_ENABLE = BIT(5),
};

#define WINDOW_DIM(l, h)        ((((l) & 255) << 8) | ((h) & 255))

_LIBSEVEN_EXTERN_C_END
