/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

struct BitUnPackParam
{
    uint16_t src_length;     // in bytes
    uint8_t  src_width;      // width of each src element (1, 2, 4, 8)
    uint8_t  dst_width;      // width of each dst element (1, 2, 4, 8, 16, 32)
    uint32_t offset:31;      // value to add to each dst element
    uint32_t keep_zeroes:1;  // whether to add offset to zero elements too
};

extern void biosBitUnPack(
        const void *src,
        void *dst,
        const struct BitUnPackParam *param);

extern void biosLZ77UnCompWram(const void *src, void *dst);
extern void biosLZ77UnCompVram(const void *src, void *dst);
extern void biosHuffUnComp(const void *src, void *dst);
extern void biosRLUnCompWram(const void *src, void *dst);
extern void biosRLUnCompVram(const void *src, void *dst);
extern void biosDiff8bitUnFilterWram(const void *src, void *dst);
extern void biosDiff8bitUnFilterVram(const void *src, void *dst);
extern void biosDiff16bitUnFilter(const void *src, void *dst);

_LIBSEVEN_EXTERN_C_END
