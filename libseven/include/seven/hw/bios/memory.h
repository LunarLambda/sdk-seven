/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

enum CpuSetFlags
{
    CS_SRC_FIXED        = BIT(24),
    CS_32BIT            = BIT(26),
    CS_16BIT            = !CS_32BIT,
};

enum CpuFastSetFlags
{
    CFS_SRC_FIXED       = BIT(24),
};

extern void biosCpuSet(const void *src, void *dst, uint32_t ctrl);
extern void biosCpuFastSet(const void *src, void *dst, uint32_t ctrl);

_LIBSEVEN_EXTERN_C_END
