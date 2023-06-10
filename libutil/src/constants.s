@
@ This Source Code Form is subject to the terms of the Mozilla Public
@ License, v. 2.0. If a copy of the MPL was not distributed with this
@ file, You can obtain one at https://mozilla.org/MPL/2.0/.
@

.equiv  REG_BASE,       0x04000000

.equiv  REG_DMA0SRC,    0x040000B0
.equiv  REG_DMA0CNT,    0x040000BA
.equiv  REG_DMA1SRC,    0x040000BC
.equiv  REG_DMA1CNT,    0x040000C6
.equiv  REG_DMA2SRC,    0x040000C8
.equiv  REG_DMA2CNT,    0x040000D2
.equiv  REG_DMA3SRC,    0x040000D4
.equiv  REG_DMA3CNT,    0x040000DE
.equiv  REG_TM0VAL,     0x04000100
.equiv  REG_TM0CNT,     0x04000102
.equiv  REG_TM1VAL,     0x04000104
.equiv  REG_TM1CNT,     0x04000106
.equiv  REG_TM2VAL,     0x04000108
.equiv  REG_TM2CNT,     0x0400010A
.equiv  REG_TM3VAL,     0x0400010C
.equiv  REG_TM3CNT,     0x0400010E
.equiv  REG_KEYINPUT,   0x04000130
.equiv  REG_KEYCNT,     0x04000132
.equiv  REG_IE,         0x04000200
.equiv  REG_IF,         0x04000202
.equiv  REG_WAITCNT,    0x04000204
.equiv  REG_IME,        0x04000208

.equiv  SOUND_FIFO_A,   0x040000A0
.equiv  SOUND_FIFO_B,   0x040000A4

.equiv  REG_IFBIOS,     0x03FFFFF8
.equiv  IRQ_HANDLER,    0x03FFFFFC

.equiv  KEY_A,          1 << 0
.equiv  KEY_B,          1 << 1
.equiv  KEY_SELECT,     1 << 2
.equiv  KEY_START,      1 << 3
.equiv  KEY_RIGHT,      1 << 4
.equiv  KEY_LEFT,       1 << 5
.equiv  KEY_UP,         1 << 6
.equiv  KEY_DOWN,       1 << 7
.equiv  KEY_R,          1 << 8
.equiv  KEY_L,          1 << 9

.equiv  KEY_INDEX_A,         0
.equiv  KEY_INDEX_B,         1
.equiv  KEY_INDEX_SELECT,    2
.equiv  KEY_INDEX_START,     3
.equiv  KEY_INDEX_RIGHT,     4
.equiv  KEY_INDEX_LEFT,      5
.equiv  KEY_INDEX_UP,        6
.equiv  KEY_INDEX_DOWN,      7
.equiv  KEY_INDEX_R,         8
.equiv  KEY_INDEX_L,         9

.equiv  TIMER_FREQ_CASCADE,     4 << 0
.equiv  TIMER_ENABLE,           1 << 7

@ vim: ft=armv4 et sta sw=4 sts=8
