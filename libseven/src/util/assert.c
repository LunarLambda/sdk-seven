/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <stdlib.h>

#include <seven/hw/irq.h>
#include <seven/util/assert.h>

static struct {
    AssertHandlerFn *handler;
    u32 panic;
} ASSERT;

extern AssertHandlerFn* assertSetHandler(AssertHandlerFn *handler)
{
    AssertHandlerFn *previous = ASSERT.handler;
    ASSERT.handler = handler;
    return previous;
}

extern AssertHandlerFn* assertGetHandler(void)
{
    return ASSERT.handler;
}

extern void _LIBSEVEN_NORETURN assertRaise(
        const char *message,
        const char *function,
        const char *file,
        u32 line)
{
    REG_IME = 0;

    AssertHandlerFn *h = ASSERT.handler;

    // Prevent a nested assert
    if (h && !ASSERT.panic)
    {
        ASSERT.panic = 1;
        h(message, function, file, line);
    }

    _Exit(EXIT_FAILURE);
}
