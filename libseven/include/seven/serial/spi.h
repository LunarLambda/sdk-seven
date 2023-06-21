/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

enum SerialControlSPI
{
    #define BF_SPI_CLOCK_OFF 0
    #define BF_SPI_CLOCK_LEN 2

    #define SPI_CLOCK(n) BITFIELD(SPI_CLOCK, (n))

    SPI_CLOCK_EXTERNAL = SPI_CLOCK(0),
    SPI_CLOCK_256KHZ = SPI_CLOCK(1),
    SPI_CLOCK_2MHZ = SPI_CLOCK(3),

    SPI_SI_STATE = BIT(2),

    SPI_SO_HIGH = BIT(3),
    SPI_SO_LOW = !SPI_SO_HIGH,

    SPI_START = BIT(7),
};

_LIBSEVEN_EXTERN_C_END
