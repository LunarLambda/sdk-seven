/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef _LIBSEVEN_HW_BIOS_AFFINE_H
#define _LIBSEVEN_HW_BIOS_AFFINE_H

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

struct BgAffineSrcData
{
    int32_t src_center_x;
    int32_t src_center_y;
    int16_t disp_center_x;
    int16_t disp_center_y;
    int16_t ratio_x;
    int16_t ratio_y;
    uint16_t theta;
};

struct BgAffineDstData
{
    int16_t h_diff_x;
    int16_t v_diff_x;
    int16_t h_diff_y;
    int16_t v_diff_y;
    int32_t start_x;
    int32_t start_y;
};

extern void biosBgAffineSet(
    const struct BgAffineSrcData *src,
    struct BgAffineDstData *dst,
    uint32_t num);

struct ObjAffineSrcData
{
    int16_t ratio_x;
    int16_t ratio_y;
    uint16_t theta;
    // BIOS wants this type to be 8 bytes but doesn't need alignment > 2
    uint8_t pad[2];
};

struct ObjAffineDstData
{
    int16_t h_diff_x;
    int16_t v_diff_x;
    int16_t h_diff_y;
    int16_t v_diff_y;
};

enum ObjAffineSetOffset
{
    OAS_OFFSET_DSTDATA = 2,
    OAS_OFFSET_OAM     = 8,
};

extern void biosObjAffineSet(
        const struct ObjAffineSrcData *src,
        void *dst,
        uint32_t num,
        uint32_t offset);

_LIBSEVEN_EXTERN_C_END

#endif /* !_LIBSEVEN_HW_BIOS_AFFINE_H */
