/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

#define REG_MOSAIC VOLADDR(0x0400004C, uint16_t)

#define BF_MOSAIC_BG_H_OFF  0
#define BF_MOSAIC_BG_H_LEN  4

#define MOSAIC_BG_H(v) BITFIELD(MOSAIC_BG_H, (v))

#define BF_MOSAIC_BG_V_OFF  4
#define BF_MOSAIC_BG_V_LEN  4

#define MOSAIC_BG_V(v) BITFIELD(MOSAIC_BG_V, (v))

#define BF_MOSAIC_OBJ_H_OFF 8
#define BF_MOSAIC_OBJ_H_LEN 4

#define MOSAIC_OBJ_H(v) BITFIELD(MOSAIC_OBJ_H, (v))

#define BF_MOSAIC_OBJ_V_OFF 12
#define BF_MOSAIC_OBJ_V_LEN 4

#define MOSAIC_OBJ_V(v) BITFIELD(MOSAIC_OBJ_V, (v))

_LIBSEVEN_EXTERN_C_END
