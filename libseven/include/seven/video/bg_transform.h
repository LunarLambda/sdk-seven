/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>
#include <seven/video/types.h>

_LIBSEVEN_EXTERN_C

#define REG_BG2PA  VOLADDR(0x04000020, int16_t)
#define REG_BG2PB  VOLADDR(0x04000022, int16_t)
#define REG_BG2PC  VOLADDR(0x04000024, int16_t)
#define REG_BG2PD  VOLADDR(0x04000026, int16_t)

#define REG_BG2MAT VOLADDR(0x04000020, struct Matrix)

#define REG_BG2X   VOLADDR(0x04000028, int32_t)
#define REG_BG2Y   VOLADDR(0x0400002C, int32_t)

#define REG_BG3PA  VOLADDR(0x04000030, int16_t)
#define REG_BG3PB  VOLADDR(0x04000032, int16_t)
#define REG_BG3PC  VOLADDR(0x04000034, int16_t)
#define REG_BG3PD  VOLADDR(0x04000036, int16_t)

#define REG_BG3MAT VOLADDR(0x04000030, struct Matrix)

#define REG_BG3X   VOLADDR(0x04000038, int32_t)
#define REG_BG3Y   VOLADDR(0x0400003C, int32_t)

_LIBSEVEN_EXTERN_C_END
