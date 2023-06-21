/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

#define REG_BG0HOFS VOLADDR(0x04000010, uint16_t)
#define REG_BG0VOFS VOLADDR(0x04000012, uint16_t)
#define REG_BG1HOFS VOLADDR(0x04000014, uint16_t)
#define REG_BG1VOFS VOLADDR(0x04000016, uint16_t)
#define REG_BG2HOFS VOLADDR(0x04000018, uint16_t)
#define REG_BG2VOFS VOLADDR(0x0400001A, uint16_t)
#define REG_BG3HOFS VOLADDR(0x0400001C, uint16_t)
#define REG_BG3VOFS VOLADDR(0x0400001E, uint16_t)

_LIBSEVEN_EXTERN_C_END
