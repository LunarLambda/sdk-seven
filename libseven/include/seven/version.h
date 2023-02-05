/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef _LIBSEVEN_VERSION_H
#define _LIBSEVEN_VERSION_H

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

#define libsevenEmitVersionString() \
    __asm__(".section .pad,\"aR\",%progbits\n" \
            ".string \"libseven " LIBSEVEN_VERSION "\"\n" \
            ".previous\n")

_LIBSEVEN_EXTERN_C_END

#endif /* !_LIBSEVEN_VERSION_H */
