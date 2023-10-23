@
@ This Source Code Form is subject to the terms of the Mozilla Public
@ License, v. 2.0. If a copy of the MPL was not distributed with this
@ file, You can obtain one at https://mozilla.org/MPL/2.0/.
@

.syntax         unified
.cpu            arm7tdmi

.section        .pad,"aR",%progbits
.string         "minrt 0.10.0"

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
_cpuset:
    .word       __iwram_lma
    .word       __iwram_vma
    .word       __iwram_dma
    .word       __ewram_lma
    .word       __ewram_vma
    .word       __ewram_dma
    .word       __vram_lma
    .word       __vram_vma
    .word       __vram_dma
    .word       __data_lma
    .word       __data_vma
    .word       __data_dma
    .word       _zero
    .word       __bss_vma
    .word       __bss_dma
    .word       _zero
    .word       __iwram_bss_vma
    .word       __iwram_bss_dma
    .word       _zero
    .word       __ewram_bss_vma
    .word       __ewram_bss_dma
    .word       _zero
    .word       __vram_bss_vma
    .word       __vram_bss_dma
_zero:
    .word       0, 0, 0
_trap:
    b           .
_start:
    @ IRQs off
    ldr         r0, =REG_IME
    str         r0, [r0]
    adr         r1, _trap
    str         r1, [r0, -0x20C]

    @ Stack setup
    msr         cpsr_c, 0xD3
    ldr         sp, =__sp_svc
    msr         cpsr_c, 0xD2
    ldr         sp, =__sp_irq
    msr         cpsr_c, 0x1F
    ldr         sp, =__sp_sys

    @ Initialize memory segments
    adr         r4, _cpuset
1:
    ldm         r4!, {r0, r1, r2}
    cmp         r0, 0
    swine       11 << 16
    bne         1b

    @ Start
    bl          _lang_start

.section        .text._exit,"ax",%progbits
_exit:
    ldr         r1, =REG_IME
    str         r1, [r1]
    b           .

.equiv          REG_IME,        0x04000208

.global         _start, _start_rom, _exit
.weak           _exit

@ vim: ft=armv4 et sta sw=4 sts=8
