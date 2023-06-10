/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

#define REG_WAITCNT VOLADDR(0x04000204, uint16_t)

enum Waitstate
{
    #define BF_WAIT_SRAM_OFF 0
    #define BF_WAIT_SRAM_LEN 2

    #define WAIT_SRAM(n) BITFIELD(WAIT_SRAM, (n))

    WAIT_SRAM_4          = WAIT_SRAM(0),
    WAIT_SRAM_3          = WAIT_SRAM(1),
    WAIT_SRAM_2          = WAIT_SRAM(2),
    WAIT_SRAM_8          = WAIT_SRAM(3),

    #define BF_WAIT_ROM_N_OFF 2
    #define BF_WAIT_ROM_N_LEN 2

    #define WAIT_ROM_N(n) BITFIELD(WAIT_ROM_N, (n))

    WAIT_ROM_N_4         = WAIT_ROM_N(0),
    WAIT_ROM_N_3         = WAIT_ROM_N(1),
    WAIT_ROM_N_2         = WAIT_ROM_N(2),
    WAIT_ROM_N_8         = WAIT_ROM_N(3),

    #define BF_WAIT_ROM_S_OFF 4
    #define BF_WAIT_ROM_S_LEN 1

    #define WAIT_ROM_S(n) BITFIELD(WAIT_ROM_S, (n))

    WAIT_ROM_S_2         = WAIT_ROM_S(0),
    WAIT_ROM_S_1         = WAIT_ROM_S(1),

    WAIT_PREFETCH_ENABLE = BIT(14),
};

_LIBSEVEN_EXTERN_C_END
