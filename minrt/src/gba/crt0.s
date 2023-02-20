@
@ This Source Code Form is subject to the terms of the Mozilla Public
@ License, v. 2.0. If a copy of the MPL was not distributed with this
@ file, You can obtain one at https://mozilla.org/MPL/2.0/.
@

.syntax         unified
.cpu            arm7tdmi

.section        .pad,"aR",%progbits
.string         "minrt 0.8.0"

.section        .text._start_rom,"ax",%progbits
_start_rom:
    and         r0, pc, 0xFF000000
    ldr         r1, =__load

    cmp         r1, r0
    @ Wrong entrypoint, continue.
    beq         _start
    @ Wanted ROM, got RAM, give up
    bhi         .
    @ Wanted RAM, got ROM, copy
    ldr         r2, =__load_end

    @ r0 = we loaded here
    @ r1 = we want to be here
    @ r2 = end
1:
    cmp         r1, r2
    bhs         1f
    ldm         r0!, {r4, r5, r6, r7, r8, r9, r10, r11}
    stm         r1!, {r4, r5, r6, r7, r8, r9, r10, r11}
    b           1b
1:
    @ Long branch to the real _start
    @ b _start would appear to work, but would continue
    @ running code in the wrong memory segment.
    ldr         pc, =_start

.section        .text._start,"ax",%progbits
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

    @ .vram section
    ldr         r0, =__vram_vma
    ldr         r1, =__vram_lma
    ldr         r2, =__vram_len
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

    @ .iwram_bss section
    ldr         r0, =__iwram_bss_vma
    movs        r1, 0
    ldr         r2, =__iwram_bss_len
    bl          memset

    @ .ewram_bss section
    ldr         r0, =__ewram_bss_vma
    movs        r1, 0
    ldr         r2, =__ewram_bss_len
    bl          memset

    @ .vram_bss section
    ldr         r0, =__vram_bss_vma
    movs        r1, 0
    ldr         r2, =__vram_bss_len
    bl          memset

    @ .bss section
    ldr         r0, =__bss_vma
    movs        r1, 0
    ldr         r2, =__bss_len

    bl          _start_lang

pool: .pool

.section        .text._exit,"ax",%progbits
_exit:
    ldr         r1, =REG_IME
    str         r1, [r1]
    b           .

.section        .noinit,"aw",%nobits
init: .byte     0

.equiv          REG_IME,        0x04000208

.global         _start, _start_rom, _exit
.weak           _exit

@ vim: ft=armv4 et sta sw=4 sts=8
