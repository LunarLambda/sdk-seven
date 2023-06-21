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

swi_impl biosSoundBiasChange      25
swi_impl biosSoundDriverInit      26
swi_impl biosSoundDriverMode      27

swi_impl biosMidiKey2Freq         31
swi_impl biosMusicPlayerOpen      32
swi_impl biosMusicPlayerStart     33
swi_impl biosMusicPlayerStop      34
swi_impl biosMusicPlayerContinue  35
swi_impl biosMusicPlayerFadeOut   36
swi_impl biosMultiBoot            37

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

@ vim: ft=armv4 et sta sw=4 sts=8
