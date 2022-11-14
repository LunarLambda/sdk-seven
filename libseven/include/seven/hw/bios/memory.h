/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef _LIBSEVEN_HW_BIOS_MEMORY_H
#define _LIBSEVEN_HW_BIOS_MEMORY_H

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

extern void biosCpuSet(const void *src, void *dst, u32 ctrl);
extern void biosCpuFastSet(const void *src, void *dst, u32 ctrl);

_LIBSEVEN_EXTERN_C_END

#endif /* !_LIBSEVEN_HW_BIOS_MEMORY_H */
