/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>
#include <seven/hw/bios.h>

_LIBSEVEN_EXTERN_C

inline void _LIBSEVEN_NORETURN biosSoftReset(void)
{
    __asm__(_LIBSEVEN_INLINE_SWI :: [num]"I"(SWI_SOFTRESET));

    __builtin_unreachable();
}

inline void _LIBSEVEN_NORETURN biosHardReset(void)
{
    __asm__(_LIBSEVEN_INLINE_SWI :: [num]"I"(SWI_HARDRESET));

    __builtin_unreachable();
}

enum SoftResetExFlags
{
    SRE_FROM_ROM = 0,
    SRE_FROM_RAM = 1,
};

// Combines biosRegisterRamReset and biosSoftReset
// Allows reset from EWRAM, automatically unsets RRR_EWRAM
// Disables IME to prevent IRQs crashing from a dangling handler
extern void _LIBSEVEN_NORETURN biosSoftResetEx(uint8_t reset_flags, bool from_ewram);

enum RegisterRamResetFlags
{
    RRR_EWRAM           = BIT(0),
    RRR_IWRAM           = BIT(1),
    RRR_PALETTE         = BIT(2),
    RRR_VRAM            = BIT(3),
    RRR_OAM             = BIT(4),
    RRR_SIO             = BIT(5),
    RRR_SOUND           = BIT(6),
    RRR_REGISTERS       = BIT(7),
    RRR_EVERYTHING      = BITS(8),
};

inline void biosRegisterRamReset(uint8_t reset_flags)
{
    register uint8_t r0 __asm__("r0") = reset_flags;

    __asm__(_LIBSEVEN_INLINE_SWI
            : "+r"(r0)
            : [num]"I"(SWI_REGISTERRAMRESET)
            : "r1", "r3", "memory");
}

_LIBSEVEN_EXTERN_C_END
