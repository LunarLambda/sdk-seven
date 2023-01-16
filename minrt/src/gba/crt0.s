@
@ This Source Code Form is subject to the terms of the Mozilla Public
@ License, v. 2.0. If a copy of the MPL was not distributed with this
@ file, You can obtain one at https://mozilla.org/MPL/2.0/.
@

.syntax         unified
.cpu            arm7tdmi

_start:
    @ IRQs off
    ldr         r0, =REG_IME
    str         r0, [r0]

    @ Stack setup
    msr         cpsr_c, 0xD3
    ldr         sp, =__sp_svc
    msr         cpsr_c, 0xD2
    ldr         sp, =__sp_irq
    msr         cpsr_c, 0x1F
    ldr         sp, =__sp_sys

    add         r0, pc, #1
    bx          r0

.thumb
    @ .iwram section
    ldr         r0, =__iwram_vma
    ldr         r1, =__iwram_lma
    ldr         r2, =__iwram_len
    cmp         r2, 0
    beq         1f
    bl          memcpy
1:

    @ .ewram section
    ldr         r0, =__ewram_vma
    ldr         r1, =__ewram_lma
    ldr         r2, =__ewram_len
    cmp         r2, 0
    beq         1f
    bl          memcpy
1:

    @ .data section
    ldr         r0, =__data_vma
    ldr         r1, =__data_lma
    ldr         r2, =__data_len
    cmp         r2, 0
    beq         1f
    bl          memcpy
1:

    @ .persistent section
    ldr         r3, =init
    ldrb        r0, [r3]
    cmp         r0, 0
    bne         1f
    movs        r0, 1
    strb        r0, [r3]
    ldr         r0, =__persistent_vma
    ldr         r1, =__persistent_lma
    ldr         r2, =__persistent_len
    cmp         r2, 0
    beq         1f
    bl          memcpy
1:

    @ .iwram.bss section
    ldr         r0, =__iwram_bss_vma
    movs        r1, 0
    ldr         r2, =__iwram_bss_len
    bl          memset

    @ .ewram.bss section
    ldr         r0, =__ewram_bss_vma
    movs        r1, 0
    ldr         r2, =__ewram_bss_len
    bl          memset

    @ .bss section
    ldr         r0, =__bss_vma
    movs        r1, 0
    ldr         r2, =__bss_len

    @ Initialization
    bl          __libc_init_array

    @ main(0, NULL,NULL)
    movs        r0, #0 @ argc
    movs        r1, #0 @ argv
    movs        r2, #0 @ envp
    bl          main
    bl          exit

_exit:
    @ Disable IRQs and halt
    ldr         r3, =REG_IME
    strh        r3, [r3]
    b           .

pool: .pool

.section        .noinit,"aw",%nobits
init: .byte     0

.equiv          REG_IME,        0x04000208

.global         _start
.weak           _exit

@ vim: ft=armv4 et sta sw=4 sts=8
