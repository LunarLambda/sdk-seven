/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

enum SIMDMask
{
    SIMD_MASK_4X8   = 0x80808080, // 4 Bytes packed
    SIMD_MASK_2X16  = 0x80008000, // 2 Halfwords packed
    SIMD_MASK_2XRGB = 0xC210C210, // 2 RGB5 colors packed
};

extern void simdAdd(uint32_t mask, void *lhs, const void *rhs, size_t len);
extern void simdSub(uint32_t mask, void *lhs, const void *rhs, size_t len);

_LIBSEVEN_EXTERN_C_END
