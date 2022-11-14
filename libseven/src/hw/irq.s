@
@ This Source Code Form is subject to the terms of the Mozilla Public
@ License, v. 2.0. If a copy of the MPL was not distributed with this
@ file, You can obtain one at https://mozilla.org/MPL/2.0/.
@
.syntax         unified
.cpu            arm7tdmi

.include        "macros.s"
.include        "seven/asm/hw/irq.s"

CONST OFF_IE_IF,  REG_IF  - REG_IE
CONST OFF_IE_IME, REG_IME - REG_IE
CONST OFF_IE_IFBIOS, REG_IFBIOS - REG_IE

bss IRQ_CRITICAL_SECTION
    .byte       0
    .byte       0
endb

.macro reg_ie_offset val
    .hword \val - OFF_IE
.endm

rodata IRQ_SOURCES .align=2
    .hword 0x0008; reg_ie_offset 0x0004 @ LCD V-Blank, DISPSTAT
    .hword 0x0010; reg_ie_offset 0x0004 @ LCD H-Blank, DISPSTAT
    .hword 0x0020; reg_ie_offset 0x0004 @ LCD V-Count, DISPSTAT
    .hword 0x0040; reg_ie_offset 0x0102 @ Timer 0,     TM0CNT
    .hword 0x0040; reg_ie_offset 0x0106 @ Timer 1,     TM1CNT
    .hword 0x0040; reg_ie_offset 0x010A @ Timer 2,     TM2CNT
    .hword 0x0040; reg_ie_offset 0x010E @ Timer 3,     TM3CNT
    .hword 0x4000; reg_ie_offset 0x0128 @ Serial IO,   SIOCNT
    .hword 0x4000; reg_ie_offset 0x00BA @ DMA 0,       DMA0CNT
    .hword 0x4000; reg_ie_offset 0x00C6 @ DMA 1,       DMA1CNT
    .hword 0x4000; reg_ie_offset 0x00D2 @ DMA 2,       DMA2CNT
    .hword 0x4000; reg_ie_offset 0x00DE @ DMA 3,       DMA3CNT
    .hword 0x4000; reg_ie_offset 0x0132 @ Keypad,      KEYCNT
    .hword 0x0000; reg_ie_offset 0x0000 @ Cartridge,   -
endr

@ void irqInit(IRQHandler *isr);
@
fn irqInit thumb
    movs        r1, #0
    mvns        r2, r1
    ldr         r3, =REG_IE

    @ REG_IME = 0
    strh        r1, [r3, #OFF_IE_IME]
    @ REG_IE = 0
    strh        r1, [r3]
    @ REG_IF = 0xFFFF
    strh        r2, [r3, #OFF_IE_IF]

    @ IRQ_HANDLER = r0
    ldr         r1, =IRQ_HANDLER
    str         r0, [r1]

    @ REG_IME = 1
    strh        r2, [r3, #OFF_IE_IME]
    bx          lr
endfn

@ void irqInitDefault(void)
@
fn irqInitDefault thumb
    ldr         r0, =irqDefaultHandler
    b           irqInit
endfn

@ void irqInitSimple(IrqCallbackFn *f)
@
fn irqInitSimple thumb
    ldr         r1, =IRQ_CALLBACK_FN
    str         r0, [r1]
    ldr         r0, =irqSimpleHandler
    b           irqInit
endfn

@ void irqInitStub(void)
@
fn irqInitStub thumb
    ldr         r0, =irqStubHandler
    b           irqInit
endfn

@ typedef void IrqCallbackFn(u16 irqs);
@
@ bool irqCallbackSet(u16 irq, IrqCallbackFn *fn)
fn irqCallbackSet thumb
    subs        r2, r0, 1
    blo         1f
    ands        r2, r2, r0
    bne         1f

    ldr         r2, =0x09AF0000
    muls        r0, r2
    lsrs        r0, r0, 28
    lsls        r0, r0, 2
    ldr         r2, =IRQ_TABLE
    str         r1, [r2, r0]

    movs        r0, 1
    bx          lr
1:
    movs        r0, 0
    bx          lr
endfn

fn irqCallbackGet thumb
    subs        r2, r0, 1
    blo         1f
    ands        r2, r2, r0
    bne         1f

    ldr         r2, =0x09AF0000
    muls        r0, r2
    lsrs        r0, r0, 28
    lsls        r0, r0, 2
    ldr         r2, =IRQ_TABLE
    ldr         r0, [r2, r0]

    bx          lr
1:
    movs        r0, 0
    bx          lr
endfn

@ u16 irqEnable(u16 irqs)
@
@ r0    REG_IE (previous)
@ r1    &REG_IE
@ r2    REG_IME
@ r3    irqs, REG_IE (new)
fn irqEnable thumb
    @ REG_IME = 0;
    ldr         r1, =REG_IE
    ldrh        r2, [r1, #OFF_IE_IME]
    strh        r1, [r1, #OFF_IE_IME]
    @ REG_IE |= irqs;
    movs        r3, r0
    ldrh        r0, [r1]
    orrs        r3, r3, r0
    strh        r3, [r1]
    @ REG_IME = old_ime;
    strh        r2, [r1, #OFF_IE_IME]
    bx          lr
endfn

@ u16 irqDisable(u16 irqs)
@
@ r0    REG_IE (previous)
@ r1    &REG_IE
@ r2    REG_IME
@ r3    irqs, REG_IE (new)
fn irqDisable thumb
    @ REG_IME = 0;
    ldr         r1, =REG_IE
    ldrh        r2, [r1, #OFF_IE_IME]
    strh        r1, [r1, #OFF_IE_IME]
    @ REG_IE &= ~irqs;
    mvns        r3, r0
    ldrh        r0, [r1]
    ands        r3, r3, r0
    strh        r3, [r1]
    @ REG_IME = old_ime
    strh        r2, [r1, #OFF_IE_IME]
    bx          lr
endfn

@ u16 irqEnableFull(u16 irqs)
@
@ r0    REG_IE (previous)
@ r1    &REG_IE
@ r2    REG_IME
@ r3    REG_IE (new)
@
@ In loop:
@
@ r0    irqs
@ r1    REG_IE
@ r2    Register flag
@ r3    IRQ_SOURCES
@ r4    Register offset from IE
@ r5    Register value
fn irqEnableFull thumb
    @ irqs &= IRQ_MASK;
    lsls        r0, r0, #19
    lsrs        r0, r0, #19

    @ REG_IME = 0;
    ldr         r1, =REG_IE
    ldrh        r2, [r1, #OFF_IE_IME]
    strh        r1, [r1, #OFF_IE_IME]

    push        {r0, r2, r4, r5}

    ldr         r3, =IRQ_SOURCES

.Lief_loop:
    lsrs        r0, r0, #1
    bcc         .Lief_continue

    @ load from table
    ldr         r2, [r3]
    @ sign extend offset into r4
    asrs        r4, r2, #16

    ldrh        r5, [r1, r4]
    orrs        r5, r5, r2
    strh        r5, [r1, r4]

.Lief_continue:
    adds        r3, r3, #4
    cmp         r0, #0
    bne         .Lief_loop

.Lief_break:
    pop         {r0, r2, r4, r5}

    movs        r3, r0
    ldrh        r0, [r1]
    orrs        r3, r3, r0
    strh        r3, [r1]

    strh        r2, [r1, #OFF_IE_IME]
    bx          lr
endfn

@ u16 irqDisableFull(u16 irqs)
@
@ r0    REG_IE (previous)
@ r1    &REG_IE
@ r2    REG_IME
@ r3    REG_IE (new)
@
@ In loop:
@
@ r0    irqs
@ r1    &REG_IE
@ r2    Register flag
@ r3    IRQ_SOURCES
@ r4    Register offset
@ r5    Register value
fn irqDisableFull thumb
    @ irqs &= IRQ_MASK;
    lsls        r0, r0, #19
    lsrs        r0, r0, #19

    @ REG_IME = 0;
    ldr         r1, =REG_IE
    ldrh        r2, [r1, #OFF_IE_IME]
    strh        r1, [r1, #OFF_IE_IME]

    push        {r0, r2, r4, r5}

    ldr         r3, =IRQ_SOURCES
.Lidf_loop:
    lsrs        r0, r0, #1
    bcc         .Lidf_continue

    ldr         r2, [r3]
    asrs        r4, r2, #16

    ldrh        r5, [r1, r4]
    bics        r5, r5, r2
    strh        r5, [r1, r4]

.Lidf_continue:
    adds        r3, r3, #4
    cmp         r0, #0
    bne         .Lidf_loop

.Lidf_break:
    pop         {r0, r2, r4, r5}

    mvns        r3, r0
    ldrh        r0, [r1]
    ands        r3, r3, r0
    strh        r3, [r1]

    strh        r2, [r1, #OFF_IE_IME]
    bx          lr
endfn

@ void irqCriticalSectionEnter(void)
@
fn irqCriticalSectionEnter thumb
    ldr         r0, =REG_IME
    ldrh        r1, [r0]
    strh        r0, [r0]

    ldr         r2, =IRQ_CRITICAL_SECTION
    ldrb        r3, [r2]
    cmp         r3, #0
    bne         .Lecs_inc

    @ Save IME
    strb        r1, [r2, #1]

.Lecs_inc:
    adds        r3, r3, #1
    strb        r3, [r2]
    bx          lr
endfn

@ void irqCriticalSectionExit(void)
@
fn irqCriticalSectionExit thumb
    ldr         r0, =REG_IME
    ldrh        r1, [r0]
    strh        r0, [r0]

    ldr         r2, =IRQ_CRITICAL_SECTION
    ldrb        r3, [r2]
    subs        r3, r3, #1
    blo         .Lxcs_ret
    @ Store
    strb        r3, [r2]
    bne         .Lxcs_ret
    @ Restore IME
    ldrb        r1, [r2, #1]
    strh        r1, [r0]
.Lxcs_ret:
    bx          lr
endfn

@ bool irqCriticalSectionActive(void)
@
fn irqCriticalSectionActive thumb
    ldr         r0, =IRQ_CRITICAL_SECTION
    ldrb        r0, [r0]
    subs        r1, r0, #1
    sbcs        r0, r0, r1
.Lcsa_out:
    bx          lr
endfn

@ void irqFree(void (*f)(void*), void *data)
@
fn irqFree thumb
    push        {r4, r5}
    movs        r3, r0
    movs        r0, r1
    ldr         r4, =REG_IME
    ldr         r5, [r4]
    str         r4, [r4]
    bl          .Lif_bxr3
    str         r5, [r4]
    pop         {r4, r5}
    bx          lr
.Lif_bxr3:
    bx          r3
endfn

fn irqDefaultHandler arm local
    mov         r1, REG_BASE                    @ 1
    @ Post-increment so we can reach IF
    ldr         r0, [r1, OFF_IE]!               @ 3
    and         r0, r0, r0, lsr 16              @ 4

    @ Isolate lowest set bit, that's the one we'll handle
    rsb         r2, r0, 0                       @ 5
    and         r0, r0, r2                      @ 6

    @ Acknowlegde IF
    strh        r0, [r1, OFF_IE_IF]             @ 8

    @ This little dance leaves us with REG_BASE back in r1,
    @ and also lets us write only to IFBIOS,
    @ just in case that could ever be a correctness issue.
    ldr         r2, [r1, OFF_IE_IFBIOS]!        @ 11
    orr         r2, r2, r0                      @ 12
    strh        r2, [r1], 8                     @ 14

    @ Lookup the IRQ-flag in the handler table using a 16-bit Debruijn sequence.
    mov         r2, 0x09000000                  @ 15
    add         r2, r2, 0xAF0000                @ 16

    @ Faster to do r2 * r0 than r0 * r2
    @ This is because the ARM7 has a 32x8 multiplier.
    @ So the number of used bytes in the second operand
    @ determines the number of cycles taken to do the multiply.
    @
    @ The ARM ARM says "it is believed" to be valid to make Rd = Rn, although
    @ it used to be marked as UNPREDICTABLE.
    @ (THUMB-mode muls forces Rd = Rn anyway?)
    mul         r2, r2, r0                      @ 18/19
    lsr         r2, r2, 28                      @ 20
    adr         r3, IRQ_TABLE                   @ 21
    ldr         r2, [r3, r2, lsl 2]             @ 24

    @ Quick exit if NULL
    cmp         r2, 0                           @ 25
    bxeq        lr                              @ 26 28 (Exit)

    @ Save some time by assuming IME is always 1 at this point
    @
    @ Only single-cycle race conditions, async DMA, or a debugger
    @ could really cause IME to be 0 here.
    str         r1, [r1, OFF_IME]               @ 28

    @ Only needed for nested IRQs.
    mrs         r3, spsr                        @ 29
    @ Default IRQ Stack allows up to 6 nested IRQs, but only if we use the
    @ system mode stack for dispatch.
    msr         cpsr_c, #0x5F                   @ 29
    push        {r3, lr}                        @ 33

    mov         lr, pc                          @ 34
    bx          r2                              @ 37+

    pop         {r3, lr}                        @ 41
    msr         cpsr_c, #0xD2                   @ 42
    msr         spsr, r3                        @ 43

    @ Spending 2 cycles resynthesizing these is faster
    @ than spending 4 cycles pushing/popping them.
    mov         r1, REG_BASE                    @ 44
    mov         r0, 1                           @ 45
    str         r0, [r1, OFF_IME]               @ 47
    bx          lr                              @ 50+

@ 0000  0 VBLANK
@ 0001  1 HBLANK
@ 0010  2 VCOUNT
@ 0011  5 TIMER2
@ 0100  3 TIMER0
@ 0101  9 DMA1
@ 0110  6 TIMER3
@ 0111 11 DMA3
@ 1000 15 NONE
@ 1001  4 TIMER1
@ 1010  8 DMA0
@ 1011 10 DMA2
@ 1100 14 NONE
@ 1101  7 SERIAL
@ 1110 13 CART
@ 1111 12 KEY
IRQ_TABLE:
    .fill       16, 4, 0
endfn

fn irqSimpleHandler arm local
    mov         r1, #REG_BASE

    @ Get IE & IF
    ldr         r0, [r1, #OFF_IE]!
    and         r0, r0, r0, lsr #16

    @ Ack IF
    strh        r0, [r1, #OFF_IE_IF]

    @ Ack IFBIOS
    ldr         r2, [r1, #OFF_IE_IFBIOS]
    orr         r2, r2, r0
    str         r2, [r1, #OFF_IE_IFBIOS]

    ldr         r2, IRQ_CALLBACK_FN

    @ Disable IME (r12)
    ldr         r12, [r1, #OFF_IE_IME]
    str         r1, [r1, #OFF_IE_IME]

    mrs         r3, spsr
    msr         cpsr_c, #0x5F
    push        {r1, r3, r12, lr}

    mov         lr, pc
    bx          r2

    pop         {r1, r3, r12, lr}
    msr         cpsr_c, #0xD2
    msr         spsr, r3

    str         r12, [r1, #OFF_IE_IME]
    bx          lr
IRQ_CALLBACK_FN:
    .word       0
endfn

fn irqStubHandler arm local
    mov         r1, #REG_BASE

    @ Get IE & IF
    ldr         r0, [r1, #OFF_IE]!
    and         r0, r0, r0, lsr #16

    @ Ack IF
    strh        r0, [r1, #OFF_IE_IF]

    @ Ack IFBIOS
    ldr         r2, [r1, #OFF_IE_IFBIOS]!
    orr         r2, r2, r0
    strh        r2, [r1], 8

    bx          lr
endfn

@ vim: ft=armv4 et sta sw=4 sts=8
