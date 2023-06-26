#include <seven/base.h>
#include <seven/bios.h>
#include <seven/irq.h>

// Special inline assembler snippet to select the correct SWI number
// depending on CPU mode. %[num] for THUMB, and %[num] << 16 for ARM.
//
// Works by checking the size of the swi instruction itself (always 4 for ARM).
#define SWI_ASM "swi %[num] << ((1f - . == 4) * -16); 1:"

// SWI 0 - SoftReset
_LIBSEVEN_NORETURN
extern void biosSoftReset(void)
{
    REG_IME = 0;

    __asm__ (SWI_ASM :: [num]"I"(SWI_SOFTRESET));

    __builtin_unreachable();
}

// SWI 1 - RegisterRamReset
extern void biosRegisterRamReset(uint8_t reset_flags)
{
    register uint8_t r0 __asm__("r0") = reset_flags;

    __asm__ volatile (SWI_ASM
            : "+r"(r0)
            : [num]"I"(SWI_REGISTERRAMRESET)
            : "r1", "r3", "memory");
}

// SWI 2 - Halt
extern void biosHalt(void)
{
    __asm__ (SWI_ASM :: [num]"I"(SWI_HALT));
}

// SWI 3 - Stop
extern void biosStop(void)
{
    __asm__ (SWI_ASM :: [num]"I"(SWI_STOP));
}

// SWI 4 - IntrWait
extern void biosIntrWait(bool wait_next, uint16_t intr_flags)
{
    register bool r0 __asm__("r0") = wait_next;
    register uint16_t r1 __asm__("r1") = intr_flags;

    __asm__ volatile (SWI_ASM
            : "+r"(r0)
            : "r"(r1), [num]"I"(SWI_INTRWAIT)
            : "r3");
}

// SWI 5 - VBlankIntrWait
extern void biosVBlankIntrWait(void)
{
    __asm__ (SWI_ASM :: [num]"I"(SWI_VBLANKINTRWAIT) : "r0", "r1", "r3");
}

// SWI 6 - Div
extern int32_t biosDiv(int32_t numerator, int32_t denominator)
{
    register int32_t r0 __asm__("r0") = numerator;
    register int32_t r1 __asm__("r1") = denominator;

    __asm__ (SWI_ASM
            : "+r"(r0), "+r"(r1)
            : [num]"I"(SWI_DIV)
            : "r3");

    return r0;
}

// SWI 6 - Div
extern int32_t biosMod(int32_t numerator, int32_t denominator)
{
    register int32_t r0 __asm__("r0") = numerator;
    register int32_t r1 __asm__("r1") = denominator;

    __asm__ (SWI_ASM
            : "+r"(r0), "+r"(r1)
            : [num]"I"(SWI_DIV)
            : "r3");

    return r1;
}

// SWI 6 - Div
extern struct Div biosDivMod(int32_t numerator, int32_t denominator)
{
    register int32_t r0 __asm__("r0") = numerator;
    register int32_t r1 __asm__("r1") = denominator;

    __asm__ (SWI_ASM
            : "+r"(r0), "+r"(r1)
            : [num]"I"(SWI_DIV)
            : "r3");

    return (struct Div) { r0, r1 };
}

// SWI 7 - DivArm (Intentionally Unimplemented)

// SWI 8 - Sqrt
extern uint32_t biosSqrt(uint32_t x)
{
    register uint32_t r0 __asm__("r0") = x;

    __asm__ (SWI_ASM
            : "+r"(r0)
            : [num]"I"(SWI_SQRT)
            : "r1", "r3");

    return r0;
}

// SWI 9 - ArcTan
extern int16_t biosArcTan(int16_t tan)
{
    register int16_t r0 __asm__("r0") = tan;

    __asm__ (SWI_ASM
            : "+r"(r0)
            : [num]"I"(SWI_ARCTAN)
            : "r1", "r3");

    return r0;
}

// SWI 10 - ArcTan2
extern uint16_t biosArcTan2(int16_t x, int16_t y)
{
    register uint16_t r0 __asm__("r0") = x;
    register uint16_t r1 __asm__("r1") = y;

    __asm__ (SWI_ASM
            : "+r"(r0), "+r"(r1)
            : [num]"I"(SWI_ARCTAN2)
            : "r3");

    return r0;
}

// SWI 11 - CpuSet
extern void biosCpuSet(const void *src, void *dst, uint32_t ctrl)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;
    register uint32_t r2 __asm__("r2") = ctrl;

    __asm__ (SWI_ASM
            : "+r"(r0), "+r"(r1), "+r"(r2), "=m"(*(uint8_t (*) [])r1)
            : [num]"I"(SWI_CPUSET), "m"(*(uint8_t (*) [])r0)
            : "r3");
}

// SWI 12 - CpuFastSet
extern void biosCpuFastSet(const void *src, void *dst, uint32_t ctrl)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;
    register uint32_t r2 __asm__("r2") = ctrl;

    __asm__ (SWI_ASM
            : "+r"(r0), "+r"(r1), "+r"(r2), "=m"(*(uint8_t (*) [])r1)
            : [num]"I"(SWI_CPUFASTSET), "m"(*(uint8_t (*) [])r0)
            : "r3");
}

// SWI 13 - "BiosChecksum" (Undocumented)
extern uint32_t biosChecksum(void)
{
    register uint32_t r0 __asm__("r0");

    __asm__ (SWI_ASM
            : "=r"(r0)
            : [num]"I"(SWI_BIOSCHECKSUM)
            : "r1", "r3");

    return r0;
}

// SWI 14 - BgAffineSet
extern void biosBgAffineSet(
    const struct BgAffineSrcData *src,
    struct BgAffineDstData *dst,
    uint32_t num)
{
    register const struct BgAffineSrcData *r0 __asm__("r0") = src;
    register struct BgAffineDstData *r1 __asm__("r1") = dst;
    register uint32_t r2 __asm__("r2") = num;

    __asm__ (SWI_ASM
            : "+r"(r0), "+r"(r1), "+r"(r2), "=m"(*(struct BgAffineDstData (*) [])r1)
            : [num]"I"(SWI_BGAFFINESET), "m"(*(struct BgAffineSrcData (*) [])r0)
            : "r3");
}

// SWI 15 - ObjAffineSet
extern void biosObjAffineSet(
        const struct ObjAffineSrcData *src,
        void *dst,
        uint32_t num,
        uint32_t offset)
{
    register const struct ObjAffineSrcData *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;
    register uint32_t r2 __asm__("r2") = num;
    register uint32_t r3 __asm__("r3") = offset;

    __asm__ (SWI_ASM
            : "+r"(r0), "+r"(r1), "+r"(r2), "+r"(r3), "=m"(*(uint8_t (*) [])r1)
            : [num]"I"(SWI_OBJAFFINESET), "m"(*(const struct ObjAffineSrcData (*) [])r0));
}

// SWI 16 - BitUnPack
extern void biosBitUnPack(
        const void *src,
        void *dst,
        const struct BitUnPackParam *param)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;
    register const struct BitUnPackParam *r2 __asm__("r2") = param;

    __asm__ (SWI_ASM
            : "+r"(r0), "+r"(r1), "+r"(r2), "=m"(*(uint8_t (*) [])r0)
            : [num]"I"(SWI_BITUNPACK), "m"(*(uint8_t (*) [])r1)
            : "r3");
}

// SWI 17 - LZ77UnCompWram
extern void biosLZ77UnCompWram(const void *src, void *dst)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;

    __asm__ (SWI_ASM
            : "+r"(r0), "+r"(r1), "=m"(*(uint8_t (*) [])r1)
            : [num]"I"(SWI_LZ77UNCOMPWRAM), "m"(*(uint8_t (*) [])r0)
            : "r3");
}

// SWI 18 - LZ77UnCompVram
extern void biosLZ77UnCompVram(const void *src, void *dst)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;

    __asm__ (SWI_ASM
            : "+r"(r0), "+r"(r1), "=m"(*(uint8_t (*) [])r1)
            : [num]"I"(SWI_LZ77UNCOMPVRAM), "m"(*(uint8_t (*) [])r0)
            : "r3");
}

// SWI 19 - HuffUnComp
extern void biosHuffUnComp(const void *src, void *dst)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;

    __asm__ (SWI_ASM
            : "+r"(r0), "+r"(r1), "=m"(*(uint8_t (*) [])r1)
            : [num]"I"(SWI_HUFFUNCOMP), "m"(*(uint8_t (*) [])r0)
            : "r3");
}

// SWI 20 - RLUnCompWram
extern void biosRLUnCompWram(const void *src, void *dst)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;

    __asm__ (SWI_ASM
            : "+r"(r0), "+r"(r1), "=m"(*(uint8_t (*) [])r1)
            : [num]"I"(SWI_RLUNCOMPWRAM), "m"(*(uint8_t (*) [])r0)
            : "r3");
}

// SWI 21 - RLUnCompVram
extern void biosRLUnCompVram(const void *src, void *dst)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;

    __asm__ (SWI_ASM
            : "+r"(r0), "+r"(r1), "=m"(*(uint8_t (*) [])r1)
            : [num]"I"(SWI_RLUNCOMPVRAM), "m"(*(uint8_t (*) [])r0)
            : "r3");
}

// SWI 22 - Diff8bitUnFilterWram
extern void biosDiff8bitUnFilterWram(const void *src, void *dst)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;

    __asm__ (SWI_ASM
            : "+r"(r0), "+r"(r1), "=m"(*(uint8_t (*) [])r1)
            : [num]"I"(SWI_DIFF8BITUNFILTERWRAM), "m"(*(uint8_t (*) [])r0)
            : "r3");
}

// SWI 23 - Diff8bitUnFilterVram
extern void biosDiff8bitUnFilterVram(const void *src, void *dst)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;

    __asm__ (SWI_ASM
            : "+r"(r0), "+r"(r1), "=m"(*(uint8_t (*) [])r1)
            : [num]"I"(SWI_DIFF8BITUNFILTERVRAM), "m"(*(uint8_t (*) [])r0)
            : "r3");
}

// SWI 24 - Diff16bitUnFilter
extern void biosDiff16bitUnFilter(const void *src, void *dst)
{
    register const void *r0 __asm__("r0") = src;
    register void *r1 __asm__("r1") = dst;

    __asm__ (SWI_ASM
            : "+r"(r0), "+r"(r1), "=m"(*(uint8_t (*) [])r1)
            : [num]"I"(SWI_DIFF16BITUNFILTER), "m"(*(uint8_t (*) [])r0)
            : "r3");
}

// SWI 25 - SoundBiasChange
// SWI 26 - SoundDriverInit
// SWI 27 - SoundDriverMode

// SWI 28 - SoundDriverMain
extern void biosSoundDriverMain(void)
{
    __asm__ (SWI_ASM
            :: [num]"I"(SWI_SOUNDDRIVERMAIN) : "r0", "r1", "r3");
}

// SWI 29 - SoundDriverVSync
extern void biosSoundDriverVSync(void)
{
    __asm__ (SWI_ASM
            :: [num]"I"(SWI_SOUNDDRIVERVSYNC) : "r0", "r1", "r3");
}

// SWI 30 - SoundChannelClear
extern void biosSoundChannelClear(void)
{
    __asm__ (SWI_ASM
            :: [num]"I"(SWI_SOUNDCHANNELCLEAR) : "r0", "r1", "r3");
}

// SWI 31 - MidiKey2Freq
// SWI 32 - MusicPlayerOpen
// SWI 33 - MusicPlayerStart
// SWI 34 - MusicPlayerStop
// SWI 35 - MusicPlayerContinue
// SWI 36 - MusicPlayerFadeOut
// SWI 37 - MultiBoot

// SWI 38 - "HardReset" (Undocumented)
_LIBSEVEN_NORETURN
extern void biosHardReset(void)
{
    REG_IME = 0;

    __asm__ (SWI_ASM :: [num]"I"(SWI_HARDRESET));

    __builtin_unreachable();
}

// SWI 39 (Undocumented, Intentionally Unimplemented)

// SWI 40 - SoundDriverVSyncOff
extern void biosSoundDriverVSyncOff(void)
{
    __asm__ (SWI_ASM
            :: [num]"I"(SWI_SOUNDDRIVERVSYNCOFF) : "r0", "r1", "r3");
}

// SWI 41 - SoundDriverVSyncOn
extern void biosSoundDriverVSyncOn(void)
{
    __asm__ (SWI_ASM
            :: [num]"I"(SWI_SOUNDDRIVERVSYNCON) : "r0", "r1", "r3");
}

// SWI 42 (Undocumented, Intentionally Unimplemented)
