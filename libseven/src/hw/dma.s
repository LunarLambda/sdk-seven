@
@ This Source Code Form is subject to the terms of the Mozilla Public
@ License, v. 2.0. If a copy of the MPL was not distributed with this
@ file, You can obtain one at https://mozilla.org/MPL/2.0/.
@

.syntax         unified
.cpu            arm7tdmi

.include        "constants.s"
.include        "macros.s"

fn dmaSet thumb
    @ Bounds check
    cmp         r0, #3
    bhi         1f
    push        {r4, r5}

    @ Register address
    movs        r4, 12
    muls        r0, r4
    ldr         r4, =REG_DMA0SRC
    adds        r0, r0, r4

    @ Write with STM to prevent interrupts from IRQ or DMA
    stm         r0!, {r1, r2, r3}
    pop         {r4, r5}
1:
    bx          lr
endfn

@ vim: ft=armv4 et sta sw=4 sts=8
