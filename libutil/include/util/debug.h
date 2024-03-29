/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

enum DebugException
{
    EXCEPTION_UNDEFINED_INSTRUCTION = 0,
    EXCEPTION_PREFETCH_ABORT = 1,
    EXCEPTION_DATA_ABORT = 2,
    EXCEPTION_IRQ = 3,
    EXCEPTION_FIQ = 4,
};

// Emulates entry to the given exception vector
bool dbgRaiseException(uint32_t exception);

_LIBSEVEN_EXTERN_C_END

