/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>
#include <seven/video/types.h>

_LIBSEVEN_EXTERN_C

#define BF_COLOR_R_OFF 0
#define BF_COLOR_R_LEN 5

#define COLOR_R(n) BITFIELD(COLOR_R, (n))

#define BF_COLOR_G_OFF 5
#define BF_COLOR_G_LEN 5

#define COLOR_G(n) BITFIELD(COLOR_G, (n))

#define BF_COLOR_B_OFF 10
#define BF_COLOR_B_LEN 5

#define COLOR_B(n) BITFIELD(COLOR_B, (n))

#define RGB5(r, g, b) \
    ((uint16_t)(COLOR_R((r)) | COLOR_G((g)) | COLOR_B((b))))

#define RGB8(r, g, b) \
    RGB5((r) >> 3, (g) >> 3, (b) >> 3)

_LIBSEVEN_EXTERN_C_END
