/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

inline void biosSoundDriverMain(void)
{
    __asm__(_LIBSEVEN_INLINE_SWI
            :: [num]"I"(SWI_SOUNDDRIVERMAIN) : "r0", "r1", "r3");
}

inline void biosSoundDriverVSync(void)
{
    __asm__(_LIBSEVEN_INLINE_SWI
            :: [num]"I"(SWI_SOUNDDRIVERVSYNC) : "r0", "r1", "r3");
}

inline void biosSoundChannelClear(void)
{
    __asm__(_LIBSEVEN_INLINE_SWI
            :: [num]"I"(SWI_SOUNDCHANNELCLEAR) : "r0", "r1", "r3");
}

inline void biosSoundDriverVSyncOff(void)
{
    __asm__(_LIBSEVEN_INLINE_SWI
            :: [num]"I"(SWI_SOUNDDRIVERVSYNCOFF) : "r0", "r1", "r3");
}

inline void biosSoundDriverVSyncOn(void)
{
    __asm__(_LIBSEVEN_INLINE_SWI
            :: [num]"I"(SWI_SOUNDDRIVERVSYNCON) : "r0", "r1", "r3");
}

_LIBSEVEN_EXTERN_C_END
