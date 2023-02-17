/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

enum RControlRaw
{
    RAW_SC_DIR_OUT    = BIT(4),
    RAW_SC_DIR_IN     = !RAW_SC_DIR_OUT,

    RAW_SD_DIR_OUT    = BIT(5),
    RAW_SD_DIR_IN     = !RAW_SD_DIR_OUT,

    RAW_SI_DIR_OUT    = BIT(6),
    RAW_SI_DIR_IN     = !RAW_SI_DIR_OUT,

    RAW_SO_DIR_OUT    = BIT(7),
    RAW_SO_DIR_IN     = !RAW_SO_DIR_OUT,

    RAW_SI_IRQ_ENABLE = BIT(8),
};

_LIBSEVEN_EXTERN_C_END
