/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

#define REG_TM0VAL VOLADDR(0x04000100, uint16_t)
#define REG_TM0CNT VOLADDR(0x04000102, uint16_t)

#define REG_TM1VAL VOLADDR(0x04000104, uint16_t)
#define REG_TM1CNT VOLADDR(0x04000106, uint16_t)

#define REG_TM2VAL VOLADDR(0x04000108, uint16_t)
#define REG_TM2CNT VOLADDR(0x0400010A, uint16_t)

#define REG_TM3VAL VOLADDR(0x0400010C, uint16_t)
#define REG_TM3CNT VOLADDR(0x0400010E, uint16_t)

enum TimerControl
{
    #define BF_TIMER_FREQ_OFF 0
    #define BF_TIMER_FREQ_LEN 3

    #define TIMER_FREQ(n) BITFIELD(TIMER_FREQ, (n))

    TIMER_FREQ_16MHZ    = TIMER_FREQ(0),
    TIMER_FREQ_262KHZ   = TIMER_FREQ(1),
    TIMER_FREQ_64KHZ    = TIMER_FREQ(2),
    TIMER_FREQ_16KHZ    = TIMER_FREQ(3),
    TIMER_FREQ_CASCADE  = TIMER_FREQ(4),
    TIMER_IRQ_ENABLE    = BIT(6),
    TIMER_ENABLE        = BIT(7),
};

// Convert a number of ticks at the given frequency to a duration in seconds.
//
// Takes one of the TIMER_FREQ values above.
extern uint32_t timerTicksToSecs(uint32_t ticks, uint32_t freq);

// Convert a number of ticks at the given frequency to a duration in milliseconds.
//
// Takes one of the TIMER_FREQ values above.
extern uint32_t timerTicksToMillis(uint32_t ticks, uint32_t freq);

// Convert a number of CPU cycles to a duration in microseconds.
extern uint32_t timerCyclesToMicros(uint32_t cycles);

// Start a cascade of two timers.
extern void timerCascadeStart(uint32_t tm_num);

// Stop a cascade of two timers.
extern void timerCascadeStop(uint32_t tm_num);

// Read the value of two cascaded timers without stopping them.
//
// If the timers are running and both timers overflow while reading their values,
// the result will be incorrect if the upper timer has a reload value other than 0.
extern uint32_t timerCascadeRead(uint32_t tm_num);

_LIBSEVEN_EXTERN_C_END
