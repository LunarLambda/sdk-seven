/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef _LIBSEVEN_BASE_VERSION_H
#define _LIBSEVEN_BASE_VERSION_H

#include <seven/base.h>

#define LIBSEVEN_VERSION_MAJOR 0
#define LIBSEVEN_VERSION_MINOR 14
#define LIBSEVEN_VERSION_PATCH 1

#define LIBSEVEN_VERSION \
    _LIBSEVEN_STR2(LIBSEVEN_VERSION_MAJOR) "." \
    _LIBSEVEN_STR2(LIBSEVEN_VERSION_MINOR) "." \
    _LIBSEVEN_STR2(LIBSEVEN_VERSION_PATCH)

#define libsevenEmitVersionString() \
    __asm__(".section .pad,\"aR\",%progbits\n" \
            ".string \"libseven " LIBSEVEN_VERSION "\"\n" \
            ".previous\n")

#endif /* !_LIBSEVEN_BASE_VERSION_H */

