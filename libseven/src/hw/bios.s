@
@ This Source Code Form is subject to the terms of the Mozilla Public
@ License, v. 2.0. If a copy of the MPL was not distributed with this
@ file, You can obtain one at https://mozilla.org/MPL/2.0/.
@

.syntax         unified
.cpu            arm7tdmi

.include        "macros.s"

.macro swi_impl name:req num:req noreturn
    fn \name thumb
        swi     #\num
        .ifnc \noreturn,noreturn
            bx  lr
        .endif
    endfn
.endm

swi_impl biosRegisterRamReset      1
swi_impl biosHalt                  2
swi_impl biosStop                  3
swi_impl biosIntrWait              4
swi_impl biosVBlankIntrWait        5
swi_impl biosDiv                   6
swi_impl biosSqrt                  8
swi_impl biosArcTan                9
swi_impl biosArcTan2              10
swi_impl biosCpuSet               11
swi_impl biosCpuFastSet           12
swi_impl biosChecksum             13
swi_impl biosBgAffineSet          14
swi_impl biosObjAffineSet         15
swi_impl biosBitUnPack            16
swi_impl biosLZ77UnCompWram       17
swi_impl biosLZ77UnCompVram       18
swi_impl biosHuffUnComp           19
swi_impl biosRLUnCompWram         20
swi_impl biosRLUnCompVram         21
swi_impl biosDiff8bitUnFilterWram 22
swi_impl biosDiff8bitUnFilterVram 23
swi_impl biosDiff16bitUnFilter    24
swi_impl biosSoundBiasChange      25
swi_impl biosSoundDriverInit      26
swi_impl biosSoundDriverMode      27
swi_impl biosSoundDriverMain      28
swi_impl biosSoundDriverVSync     29
swi_impl biosSoundChannelClear    30
swi_impl biosMidiKey2Freq         31
swi_impl biosMusicPlayerOpen      32
swi_impl biosMusicPlayerStart     33
swi_impl biosMusicPlayerStop      34
swi_impl biosMusicPlayerContinue  35
swi_impl biosMusicPlayerFadeOut   36
swi_impl biosMultiBoot            37
swi_impl biosSoundDriverVSyncOff  40
swi_impl biosSoundDriverVSyncOn   41

@ We do not need to fix the stack pointer here. Even if the stacks are
@ completely trashed, since SoftReset is noreturn, and the first thing it does
@ is reset the stack pointers, it's fine even if the SVC handler couldn't
@ correctly return.
@
@ We do disable IRQs however, since during the time the BIOS clears the upper
@ 512 bytes of IWRAM, including the IRQ handler pointer, interrupts aren't
@ being masked in the CPSR.
fn biosSoftReset thumb
    ldr         r2, =0x04000208
    str         r2, [r2]
    swi         0
endfn

fn biosHardReset thumb
    ldr         r2, =0x04000208
    str         r2, [r2]
    swi         38
endfn

@ Here we do fix the system mode stack pointer, since RegisterRamReset uses the
@ the stack. We assume in good faith that the SVC-mode stack pointer is fine,
@ since under any normal circumstances, including total program failure,
@ it really shouldn't be modified from it's defaults. Maybe if minrt ever
@ supports relocating the stack pointers.
fn biosSoftResetEx thumb
    ldr         r2, =0x04000208
    strh        r2, [r2]
    movs        r1, r1
    beq         1f
    movs        r2, #1
    bics        r0, r2
1:
    ldr         r2, =0x03007FFA
    strb        r1, [r2]
    subs        r2, #0xFA
    mov         sp, r2
    swi         1
    swi         0
endfn

@ Return a struct similar to C div() functions
@
@ Do some register shuffling to match the ABI of the SWI.
fn biosDivMod thumb
    movs        r3, r0
    movs        r0, r1
    movs        r1, r2
    movs        r2, r3
    swi         6
    stmia       r2!, {r0, r1}
    bx          lr
endfn

@ vim: ft=armv4 et sta sw=4 sts=8
