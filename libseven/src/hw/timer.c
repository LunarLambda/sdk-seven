#include <seven/base.h>
#include <seven/timer.h>

static uint32_t freq_to_shift(uint32_t freq)
{
    return 24 - (freq ? 2 * freq + 4 : 0);
}

extern uint32_t timerTicksToSecs(uint32_t ticks, uint32_t freq)
{
    return ticks >> freq_to_shift(freq);
}

_LIBSEVEN_TARGET_ARM
extern uint32_t timerTicksToMillis(uint32_t ticks, uint32_t freq)
{
    return ((uint64_t)ticks * 1000) >> freq_to_shift(freq);
}

_LIBSEVEN_TARGET_ARM
extern uint32_t timerCyclesToMicros(uint32_t cycles)
{
    return ((uint64_t)cycles * 1000000) >> 24;
}

extern void timerCascadeStart(uint32_t tm_num)
{
    if (tm_num > 2)
    {
        return;
    }

    volatile uint16_t *tm = &REG_TM0CNT + tm_num * 2;

    tm[2] |= TIMER_ENABLE;
    tm[0] |= TIMER_ENABLE;
}

extern void timerCascadeStop(uint32_t tm_num)
{
    if (tm_num > 2)
    {
        return;
    }

    volatile uint16_t *tm = &REG_TM0CNT + tm_num * 2;

    tm[0] &= ~TIMER_ENABLE;
    tm[2] &= ~TIMER_ENABLE;
}

extern uint32_t timerCascadeRead(uint32_t tm_num)
{
    if (tm_num > 2)
    {
        return 0;
    }

    volatile uint16_t *tm = &REG_TM0VAL + tm_num * 2;

    uint16_t l1 = tm[0];
    uint16_t h  = tm[2];
    uint16_t l2 = tm[0];

    // If the lower timer overflowed since we read the high timer,
    // bump the value up by 1. Assume the high timer doesn't overflow because
    // we can't know what reload value the user set, and in that case the
    // result would be garbage anyway.
    if (l2 < l1)
    {
        h++;
    }

    return l2 | (h << 16);
}
