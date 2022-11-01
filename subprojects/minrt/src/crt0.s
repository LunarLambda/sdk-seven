@
@ This Source Code Form is subject to the terms of the Mozilla Public
@ License, v. 2.0. If a copy of the MPL was not distributed with this
@ file, You can obtain one at https://mozilla.org/MPL/2.0/.
@

.syntax         unified
.cpu            arm7tdmi

.section        .rom_header,"ax",%progbits
.align 2
.arm
_start:
    b           entrypoint      @ ROM entry point
    .include    "header.s"
    b           entrypoint      @ Multiboot entry point
_boot_type:
    .zero       1               @ Boot type
_boot_client:
    .zero       1               @ Client number
    .zero       26              @ Reserved
    b           entrypoint      @ JOY Bus entry point

.align 2
.arm
entrypoint:
    add         r0, pc, #1
    bx          r0
.thumb
    @ IRQs off
    ldr         r3, =REG_IME
    strh        r3, [r3]

    ldr         r3, =REG_WRAMCNT
    ldr         r2, =__wramcnt
    str         r2, [r3]

    ldr         r3, =REG_DMA3

    @ .iwram section
    ldr         r0, =__iwram_lma
    ldr         r1, =__iwram_vma
    ldr         r2, =__iwram_dma
    bl          dma_copy

    @ .iwram0 section
    ldr         r0, =__load_start_iwram0
    ldr         r1, =__iwram_overlay_vma
    ldr         r2, =__iwram_overlay_dma
    bl          dma_copy

    @ .iwram_bss section
    mov         r0, sp
    ldr         r1, =__iwram_bss_vma
    ldr         r2, =__iwram_bss_dma
    bl          dma_copy

    @ .ewram section
    ldr         r0, =__ewram_lma
    ldr         r1, =__ewram_vma
    ldr         r2, =__ewram_dma
    bl          dma_copy

    @ .ewram0 section
    ldr         r0, =__load_start_ewram0
    ldr         r1, =__ewram_overlay_vma
    ldr         r2, =__ewram_overlay_dma
    bl          dma_copy

    @ .ewram_bss section
    mov         r0, sp
    ldr         r1, =__ewram_bss_vma
    ldr         r2, =__ewram_bss_dma
    bl          dma_copy

    @ .preinit_array section
    ldr         r4, =__preinit_array_start
    ldr         r5, =__preinit_array_end
    bl          init_array

    @ .init_array section
    ldr         r4, =__init_array_start
    ldr         r5, =__init_array_end
    bl          init_array

    @ main(0, NULL,NULL)
    movs        r0, #0 @ argc
    movs        r1, #0 @ argv
    movs        r2, #0 @ envp
    ldr         r3, =main
    bl          bx_r3
    movs        r7, r0

    @ .fini_array section
    ldr         r4, =__fini_array_start
    ldr         r5, =__fini_array_end
    bl          fini_array

    @ exit()
    movs        r0, r7
    ldr         r3, =exit
    bl          bx_r3

_exit:
    @ Disable IRQs and halt
    ldr         r3, =REG_IME
    strh        r3, [r3]
    1: b        1b

dma_copy:
    @ NOTE: This checks against a non-zero section size.
    @ In the case of an EWRAM section spanning all of EWRAM (256K),
    @ The lower 16-bit will be zero. This works fine for the DMA,
    @ since the lower 5 bit of DMACNT are unused.
    @ That's why we shift 15, not 16.
    lsls        r4, r2, #15
    beq         dma_skip
    stm         r3!, {r0, r1, r2}
    subs        r3, r3, #12
dma_skip:
    bx          lr

init_array:
    mov         r6, lr
    cmp         r4, r5
    beq         init_skip
init_loop:
    ldr         r3, [r4]
    bl          bx_r3
    adds        r4, r4, #4
    cmp         r4, r5
    bne         init_loop
init_skip:
    bx          r6

bx_r3:
    bx          r3

fini_array:
    mov         r6, lr
    cmp         r5, r4
    beq         fini_skip
fini_loop:
    subs        r5, r5, #4
    ldr         r3, [r5]
    bl          bx_r3
    cmp         r5, r4
    bne         fini_loop
fini_skip:
    bx          r6

pool: .pool

.equiv          REG_DMA3,       0x040000D4
.equiv          REG_IME,        0x04000208
.equiv          REG_WRAMCNT,    0x04000800
.equiv          SVC_CPUSET,     11

.global         _start, _exit, _boot_type, _boot_client
.weak           _exit

@ vim: ft=armv4 et sta sw=4 sts=8
