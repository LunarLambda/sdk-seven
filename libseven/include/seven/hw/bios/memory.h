/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>
#include <seven/hw/bios.h>

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

inline void biosCpuSet(const void *src, void *dst, uint32_t ctrl)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;
    register uint32_t r2 __asm__("r2") = ctrl;

    __asm__(_LIBSEVEN_INLINE_SWI
            : "+r"(r0), "+r"(r1), "+r"(r2)
            : [num]"I"(SWI_CPUSET)
            : "r3", "memory");
}

inline void biosCpuFastSet(const void *src, void *dst, uint32_t ctrl)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;
    register uint32_t r2 __asm__("r2") = ctrl;

    __asm__(_LIBSEVEN_INLINE_SWI
            : "+r"(r0), "+r"(r1), "+r"(r2)
            : [num]"I"(SWI_CPUFASTSET)
            : "r3", "memory");

}

_LIBSEVEN_EXTERN_C_END
