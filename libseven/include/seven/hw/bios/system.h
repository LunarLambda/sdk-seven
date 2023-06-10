/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>
#include <seven/hw/bios.h>

_LIBSEVEN_EXTERN_C

enum BiosChecksum
{
    BIOS_CHECKSUM_GBA = 0xBAAE187F,
    BIOS_CHECKSUM_NDS = 0xBAAE1880,
};

inline uint32_t biosChecksum(void)
{
    register uint32_t r0 __asm__("r0");

    __asm__(_LIBSEVEN_INLINE_SWI
            : "=r"(r0)
            : [num]"I"(SWI_BIOSCHECKSUM)
            : "r1", "r3");

    return r0;
}

_LIBSEVEN_EXTERN_C_END
