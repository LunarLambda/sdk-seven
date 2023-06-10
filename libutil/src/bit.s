@
@ This Source Code Form is subject to the terms of the Mozilla Public
@ License, v. 2.0. If a copy of the MPL was not distributed with this
@ file, You can obtain one at https://mozilla.org/MPL/2.0/.
@

.syntax         unified
.cpu            arm7tdmi

.include        "macros.s"

@ 18+ cycles
fn bitCTZ32 arm
    rsb         r1, r0, #0
    and         r0, r0, r1

    ldr         r1, =0x077CB531
    muls        r0, r1
    adr         r1, TABLE32
    ldrb        r0, [r1, r0, lsr #27]

    moveq       r0, #32
    bx          lr

@ 23+ cycles
fn bitCLZ32
    orr         r0, r0, r0, lsr #1
    orr         r0, r0, r0, lsr #2
    orr         r0, r0, r0, lsr #4
    orr         r0, r0, r0, lsr #8
    orr         r0, r0, r0, lsr #16
    sub         r0, r0, r0, lsr #1

    ldr         r1, =0x077CB531
    muls        r0, r1
    adr         r1, TABLE32
    ldrb        r0, [r1, r0, lsr #27]

    rsb         r0, r0, #31

    moveq       r0, #32
    bx          lr

TABLE32:
  .byte  0,  1, 28,  2, 29, 14, 24,  3
  .byte 30, 22, 20, 15, 25, 17,  4,  8
  .byte 31, 27, 13, 23, 21, 19, 16,  7
  .byte 26, 12, 18,  6, 11,  5, 10,  9
endfn

@ 16+ cycles
fn bitCTZ16 arm .section=.text
    rsb         r1, r0, #0
    ands        r1, r0, r1
    moveq       r0, #1
    movne       r0, #0

    tst         r1, 0xFF
    lsreq       r1, r1, #8
    addeq       r0, r0, #8

    tst         r1, 0x0F
    addeq       r0, r0, #4

    tst         r1, 0x33
    addeq       r0, r0, #2

    tst         r1, 0x55
    addeq       r0, r0, #1

    bx          lr
endfn

@ 13+ cycles
fn bitCTZ8 arm .section=.text
    rsb         r1, r0, #0
    ands        r1, r0, r1
    moveq       r0, #1
    movne       r0, #0

    tst         r1, 0x0F
    addeq       r0, r0, #4

    tst         r1, 0x33
    addeq       r0, r0, #2

    tst         r1, 0x55
    addeq       r0, r0, #1

    bx          lr
endfn

@ 19+ cycles
fn bitCLZ16 arm .section=.text
    orr         r0, r0, r0, lsr #1
    orr         r0, r0, r0, lsr #2
    orr         r0, r0, r0, lsr #4
    orr         r0, r0, r0, lsr #8
    sub         r0, r0, r0, lsr #1

    mov         r1, 0x09000000
    add         r1, r1, 0xAF0000
    muls        r0, r1
    adr         r1, TABLE16
    ldrb        r0, [r1, r0, lsr #28]

    moveq       r0, #16
    bx          lr
TABLE16:
    .byte 15, 14, 13, 10, 12,  6,  9,  4
    .byte  0, 11,  7,  5,  1,  8,  2,  3
endfn

@  15+ cycles
fn bitCLZ8 arm .section=.text
    orr         r0, r0, r0, lsr #1
    orr         r0, r0, r0, lsr #2
    orr         r0, r0, r0, lsr #4
    sub         r0, r0, r0, lsr #1

    mov         r1, #0x17000000
    muls        r0, r1
    adr         r1, TABLE8
    ldrb        r0, [r1, r0, lsr #29]

    moveq       r0, #8
    bx          lr
TABLE8:
    .byte 7, 6, 5, 3, 0, 4, 1, 2
endfn

@ vim: ft=armv4 et sta sw=4 sts=8
