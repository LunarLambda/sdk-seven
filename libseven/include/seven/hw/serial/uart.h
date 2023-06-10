/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

enum SerialControlUART
{
    #define BF_UART_BAUD_OFF 0
    #define BF_UART_BAUD_LEN 2

    #define UART_BAUD(n) BITFIELD(UART_BAUD, (n))

    UART_BAUD_9600 = UART_BAUD(0),
    UART_BAUD_38400 = UART_BAUD(1),
    UART_BAUD_57600 = UART_BAUD(2),
    UART_BAUD_115200 = UART_BAUD(3),

    UART_CTS_ENABLE = BIT(2),

    UART_PARITY_ODD = BIT(3),
    UART_PARITY_EVEN = !UART_PARITY_ODD,

    UART_SEND_FULL = BIT(4),
    UART_RECEIVE_EMPTY = BIT(5),

    UART_ERROR = BIT(6),

    UART_8BIT = BIT(8),
    UART_7BIT = !UART_8BIT,

    UART_FIFO_ENABLE = BIT(8),
    UART_PARITY_ENABLE = BIT(9),
    UART_SEND_ENABLE = BIT(10),
    UART_RECEIVE_ENABLE = BIT(11),
};

_LIBSEVEN_EXTERN_C_END
