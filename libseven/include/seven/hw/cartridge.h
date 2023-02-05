/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

// GPIO Data
#define REG_GPIODAT     VOLADDR(0x080000C4, uint16_t)
// GPIO Direction
#define REG_GPIODIR     VOLADDR(0x080000C6, uint16_t)
// GPIO Control
#define REG_GPIOCNT     VOLADDR(0x080000C8, uint16_t)

enum GpioDirection
{
    GPIO_IN  = 0,
    GPIO_OUT = 1,
};

enum GpioControl
{
    GPIO_WRITEONLY = 0,
    GPIO_READWRITE = 1,
};

_LIBSEVEN_EXTERN_C_END
