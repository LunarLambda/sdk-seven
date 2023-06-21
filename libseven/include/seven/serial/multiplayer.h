/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

enum SerialControlMultiplayer
{
    #define BF_MULTI_BAUD_OFF 0
    #define BF_MULTI_BAUD_LEN 2

    #define MULTI_BAUD(n) BITFIELD(MULTI_BAUD, (n))

    MULTI_BAUD_9600 = MULTI_BAUD(0),
    MULTI_BAUD_38400 = MULTI_BAUD(1),
    MULTI_BAUD_57600 = MULTI_BAUD(2),
    MULTI_BAUD_115200 = MULTI_BAUD(3),

    MULTI_CLIENT_FLAG = BIT(2),

    MULTI_READY_FLAG = BIT(3),

    #define BF_MULTI_CLIENT_ID_OFF 4
    #define BF_MULTI_CLIENT_ID_LEN 2

    MULTI_ERROR_FLAG = BIT(6),

    MULTI_START = BIT(7),
    MULTI_BUSY = MULTI_START,
};

_LIBSEVEN_EXTERN_C_END
