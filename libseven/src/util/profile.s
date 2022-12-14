@
@ This Source Code Form is subject to the terms of the Mozilla Public
@ License, v. 2.0. If a copy of the MPL was not distributed with this
@ file, You can obtain one at https://mozilla.org/MPL/2.0/.
@

.syntax         unified
.cpu            arm7tdmi

.include        "constants.s"
.include        "macros.s"

@ u32 profileFunction(void (*f)(void*), void *data);
@
fn profileRun arm
    push        {r4, r5, r6, lr}

    mov         r4, r0
    mov         r0, r1

    @ Setup timers
    ldr         r5, =REG_TM2VAL
    mov         r6, #TIMER_FREQ_CASCADE << 16
    mov         r1, #TIMER_ENABLE << 16
    stmia       r5, {r1, r6}

    @ Call function
    mov         lr, pc
    bx          r4

    @ Stop timer
    strh        r6, [r5, #2]

    @ Read timers
    ldrh        r0, [r5]
    ldrh        r1, [r5, #4]
    orr         r0, r0, r1, lsl #16
    @ Subtract 3 Cycles of timer start/stop delay
    sub         r0, r0, #3

    pop         {r4, r5, r6, lr}
    bx          lr
endfn

@ vim: ft=armv4 et sta sw=4 sts=8
