/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

// Measures how many CPU cycles it takes to execute the given function,
// using timers 2 and 3.
//
// data is an optional pointer to any data the function needs.
extern uint32_t profileRun(void (*function)(void*), void *data);

_LIBSEVEN_EXTERN_C_END
