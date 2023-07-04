@
@ This Source Code Form is subject to the terms of the Mozilla Public
@ License, v. 2.0. If a copy of the MPL was not distributed with this
@ file, You can obtain one at https://mozilla.org/MPL/2.0/.
@
.syntax         unified
.cpu            arm7tdmi

.include        "constants.s"
.include        "macros.s"

.equiv OFF_IE,          REG_IE - REG_BASE
.equiv OFF_IME,         REG_IME - REG_BASE
.equiv OFF_IE_IF,       REG_IF  - REG_IE
.equiv OFF_IE_IME,      REG_IME - REG_IE
.equiv OFF_IE_IFBIOS,   REG_IFBIOS - REG_IE

@ r0: REG_BASE
@ r1: Interrupt flag
@ r2: <scratch>
@ r3: Handler function
fn isrDefault arm
    @ Read IE & IF
    ldr         r1, [r0, OFF_IE]!                               @ 3
    and         r1, r1, r1, lsr 16                              @ 4

    @ Handle the lowest set IRQ
    rsb         r2, r1, 0                                       @ 5
    and         r1, r1, r2                                      @ 6

    @ Acknowlegde IF
    strh        r1, [r0, OFF_IE_IF]                             @ 8

    @ Acknowledge IFBIOS
    ldr         r2, [r0, OFF_IE_IFBIOS]!                        @ 11
    orr         r2, r2, r1                                      @ 12
    strh        r2, [r0], 8                                     @ 14

    @ Lookup the IRQ handler using a 16-bit Debruijn sequence.
    mov         r0, 0x09 << 24                                  @ 15
    orr         r0, 0xAF << 16                                  @ 16
    mul         r2, r0, r1                                      @ 18 / 19
    lsr         r2, r2, 28                                      @ 20

    @ Load handler
    adr         r3, ISR_DEFAULT_HANDLERS                        @ 21
    ldr         r3, [r3, r2, lsl 2]                             @ 24
    cmp         r3, 0                                           @ 25
    bxeq        lr                                              @ 26 / 28

    @ Enable nesting
    mrs         r2, spsr                                        @ 27
    msr         cpsr_c, 0x9F                                    @ 28
    push        {r2, lr}                                        @ 31

    @ Call
    mov         r0, r1                                          @ 32
    mov         lr, pc                                          @ 33
    bx          r3                                              @ 36

    @ Return
    pop         {r2, lr}                                        @ 40
    msr         cpsr_c, 0x92                                    @ 41
    msr         spsr, r2                                        @ 42
    bx          lr                                              @ 45
data ISR_DEFAULT_HANDLERS global .inline=1
    .fill       16, 4, 0
endd
endfn

@ r0: REG_BASE
@ r1: Interrupt flag
@ r2: <scratch>
@ r3: Handler function
fn isrMinimal arm
    @ Read IE & IF
    ldr         r1, [r0, #OFF_IE]!                              @ 3
    and         r1, r1, r1, lsr #16                             @ 4

    @ Acknowledge IF
    strh        r1, [r0, #OFF_IE_IF]                            @ 6

    @ Acknowledge IFBIOS
    ldr         r2, [r0, #OFF_IE_IFBIOS]!                       @ 9
    orr         r2, r2, r1                                      @ 10
    strh        r2, [r0], 8                                     @ 12

    @ Load handler
    ldr         r3, ISR_MINIMAL_HANDLER                         @ 15
    cmp         r3, 0                                           @ 16
    bxeq        lr                                              @ 17 / 19 (exit)

    @ Call
    mov         r0, r1                                          @ 18
    bx          r3                                              @ 21
data ISR_MINIMAL_HANDLER global .inline=1
    .word       0
endd
endfn

@ vim: ft=armv4 et sta sw=4 sts=8
