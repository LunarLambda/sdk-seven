/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

enum SoftwareInterruptNumber
{
    SWI_SOFTRESET                       =  0,
    SWI_REGISTERRAMRESET                =  1,

    SWI_HALT                            =  2,
    SWI_STOP                            =  3,
    SWI_INTRWAIT                        =  4,
    SWI_VBLANKINTRWAIT                  =  5,

    SWI_DIV                             =  6,
    SWI_SQRT                            =  8,
    SWI_ARCTAN                          =  9,
    SWI_ARCTAN2                         = 10,

    SWI_CPUSET                          = 11,
    SWI_CPUFASTSET                      = 12,

    SWI_BIOSCHECKSUM                    = 13,

    SWI_BGAFFINESET                     = 14,
    SWI_OBJAFFINESET                    = 15,

    SWI_BITUNPACK                       = 16,
    SWI_LZ77UNCOMPWRAM                  = 17,
    SWI_LZ77UNCOMPVRAM                  = 18,
    SWI_HUFFUNCOMP                      = 19,
    SWI_RLUNCOMPWRAM                    = 20,
    SWI_RLUNCOMPVRAM                    = 21,
    SWI_DIFF8BITUNFILTERWRAM            = 22,
    SWI_DIFF8BITUNFILTERVRAM            = 23,
    SWI_DIFF16BITUNFILTER               = 24,

    SWI_SOUNDBIAS                       = 25,
    SWI_SOUNDDRIVERINIT                 = 26,
    SWI_SOUNDDRIVERMODE                 = 27,
    SWI_SOUNDDRIVERMAIN                 = 28,
    SWI_SOUNDDRIVERVSYNC                = 29,
    SWI_SOUNDCHANNELCLEAR               = 30,
    SWI_MIDIKEY2FREQ                    = 31,
    SWI_MUSICPLAYEROPEN                 = 32,
    SWI_MUSICPLAYERSTART                = 33,
    SWI_MUSICPLAYERSTOP                 = 34,
    SWI_MUSICPLAYERCONTINUE             = 35,
    SWI_MUSICPLAYERFADEOUT              = 36,

    SWI_MULTIBOOT                       = 37,

    SWI_HARDRESET                       = 38,

    SWI_SOUNDDRIVERVSYNCOFF             = 40,
    SWI_SOUNDDRIVERVSYNCON              = 41,
};

enum SoftResetExFlags
{
    SRE_FROM_ROM = 0,
    SRE_FROM_RAM = 1,
};

enum RegisterRamResetFlags
{
    RRR_EWRAM           = BIT(0),
    RRR_IWRAM           = BIT(1),
    RRR_PALETTE         = BIT(2),
    RRR_VRAM            = BIT(3),
    RRR_OAM             = BIT(4),
    RRR_SIO             = BIT(5),
    RRR_SOUND           = BIT(6),
    RRR_REGISTERS       = BIT(7),
    RRR_EVERYTHING      = BITS(8),
};

struct Div
{
    int32_t quot;
    int32_t rem;
};

enum CpuSetFlags
{
    CS_SRC_FIXED        = BIT(24),
    CS_32BIT            = BIT(26),
    CS_16BIT            = !CS_32BIT,
};

enum CpuFastSetFlags
{
    CFS_SRC_FIXED       = BIT(24),
};

enum BiosChecksum
{
    BIOS_CHECKSUM_GBA = 0xBAAE187F,
    BIOS_CHECKSUM_NDS = 0xBAAE1880,
};

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

struct BitUnPackParam
{
    uint16_t src_length;     // in bytes
    uint8_t  src_width;      // width of each src element (1, 2, 4, 8)
    uint8_t  dst_width;      // width of each dst element (1, 2, 4, 8, 16, 32)
    uint32_t offset:31;      // value to add to each dst element
    uint32_t keep_zeroes:1;  // whether to add offset to zero elements too
};

_LIBSEVEN_NORETURN
extern void biosSoftReset(void);
// Combines biosRegisterRamReset and biosSoftReset
// Allows reset from EWRAM, automatically unsets RRR_EWRAM
_LIBSEVEN_NORETURN
extern void biosSoftResetEx(uint8_t reset_flags, bool from_ewram);
extern void biosRegisterRamReset(uint8_t reset_flags);
extern void biosHalt(void);
extern void biosStop(void);
extern void biosIntrWait(bool wait_next, uint16_t intr_flags);
extern void biosVBlankIntrWait(void);
extern int32_t biosDiv(int32_t numerator, int32_t denominator);
extern int32_t biosMod(int32_t numerator, int32_t denominator);
extern struct Div biosDivMod(int32_t numerator, int32_t denominator);
extern uint32_t biosSqrt(uint32_t x);
extern int16_t biosArcTan(int16_t tan);
extern uint16_t biosArcTan2(int16_t x, int16_t y);
extern void biosCpuSet(const void *src, void *dst, uint32_t ctrl);
extern void biosCpuFastSet(const void *src, void *dst, uint32_t ctrl);
extern uint32_t biosChecksum(void);
extern void biosBgAffineSet(
    const struct BgAffineSrcData *src,
    struct BgAffineDstData *dst,
    uint32_t num);
extern void biosObjAffineSet(
        const struct ObjAffineSrcData *src,
        void *dst,
        uint32_t num,
        uint32_t offset);
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
extern void biosSoundDriverMain(void);
extern void biosSoundDriverVSync(void);
extern void biosSoundChannelClear(void);
_LIBSEVEN_NORETURN
extern void biosHardReset(void);
extern void biosSoundDriverVSyncOff(void);
extern void biosSoundDriverVSyncOn(void);

_LIBSEVEN_EXTERN_C_END
