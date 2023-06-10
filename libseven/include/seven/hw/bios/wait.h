/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>
#include <seven/hw/bios.h>

_LIBSEVEN_EXTERN_C

inline void biosHalt(void)
{
    __asm__(_LIBSEVEN_INLINE_SWI :: [num]"I"(SWI_HALT) : "r0", "r1", "r3");
}

inline void biosStop(void)
{
    __asm__(_LIBSEVEN_INLINE_SWI :: [num]"I"(SWI_STOP) : "r0", "r1", "r3");
}

inline void biosIntrWait(bool wait_next, uint16_t intr_flags)
{
    register bool r0 __asm__("r0") = wait_next;
    register uint16_t r1 __asm__("r1") = intr_flags;

    __asm__(_LIBSEVEN_INLINE_SWI
            : "+r"(r0), "+r"(r1)
            : [num]"I"(SWI_INTRWAIT)
            : "r3");
}

inline void biosVBlankIntrWait(void)
{
    __asm__(_LIBSEVEN_INLINE_SWI :: [num]"I"(SWI_VBLANKINTRWAIT) : "r0", "r1", "r3");
}

_LIBSEVEN_EXTERN_C_END
