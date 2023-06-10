/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

#define REG_TM0VAL      VOLADDR(0x04000100, uint16_t)
#define REG_TM0CNT      VOLADDR(0x04000102, uint16_t)

#define REG_TM1VAL      VOLADDR(0x04000104, uint16_t)
#define REG_TM1CNT      VOLADDR(0x04000106, uint16_t)

#define REG_TM2VAL      VOLADDR(0x04000108, uint16_t)
#define REG_TM2CNT      VOLADDR(0x0400010A, uint16_t)

#define REG_TM3VAL      VOLADDR(0x0400010C, uint16_t)
#define REG_TM3CNT      VOLADDR(0x0400010E, uint16_t)

#define BF_TIMER_FREQ_OFF 0
#define BF_TIMER_FREQ_LEN 3

#define TIMER_FREQ(n) BITFIELD(TIMER_FREQ, (n))

enum TimerControl
{
    TIMER_FREQ_16MHZ    = TIMER_FREQ(0),
    TIMER_FREQ_262KHZ   = TIMER_FREQ(1),
    TIMER_FREQ_64KHZ    = TIMER_FREQ(2),
    TIMER_FREQ_16KHZ    = TIMER_FREQ(3),
    TIMER_FREQ_CASCADE  = TIMER_FREQ(4),
    TIMER_IRQ_ENABLE    = BIT(6),
    TIMER_ENABLE        = BIT(7),
};

extern void timerSet(uint32_t num, uint16_t reload, uint16_t flags);

extern void timerEnable(uint32_t num);

extern void timerDisable(uint32_t num);

extern uint16_t timerGetValue(uint32_t num);

_LIBSEVEN_EXTERN_C_END
