/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

extern void sramRead(void *dst, size_t len);

extern void sramReadAt(void *dst, size_t len, size_t off);

extern void sramWrite(const void *src, size_t len);

extern void sramWriteAt(const void *src, size_t len, size_t off);

extern size_t sramCompare(const void *src, size_t len);

extern size_t sramCompareAt(const void *src, size_t len, size_t off);

extern void sramClear(size_t len);

extern void sramClearAt(size_t len, size_t off);

extern void sramRead64(void *dst, size_t len);

extern void sramReadAt64(void *dst, size_t len, size_t off);

extern void sramWrite64(const void *src, size_t len);

extern void sramWriteAt64(const void *src, size_t len, size_t off);

extern void sramClear64(size_t len);

extern void sramClearAt64(size_t len, size_t off);

_LIBSEVEN_EXTERN_C_END
