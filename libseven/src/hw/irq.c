/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <seven/base.h>
#include <seven/irq.h>

extern IsrFn isrDefault;
extern IsrFn isrMinimal;

// Mark these as volatile because LTO cannot verify that isrDefault/isrMinimal
// is called because it's invoked indirectly through the hardware.
//
// This means LTO will consider calls to irqSetHandler and similar to be dead
// accesses, and remove them entirely
//
// For our purposes, writing these does produce a side effect, so volatile is
// actually the semantically correct option here.
extern IrqHandlerFn * volatile ISR_MINIMAL_HANDLER;
extern IrqHandlerFn * volatile ISR_DEFAULT_HANDLERS[16];

extern void irqInit(IsrFn *isr)
{
    REG_IME = 0;
    REG_IE = 0;
    REG_IF = 0xFFFF;

    MEM_ISR = isr;

    REG_IME = 1;
}

extern void irqInitDefault(void)
{
    REG_IME = 0;

    for (size_t i = 0; i < 16; i++)
    {
        ISR_DEFAULT_HANDLERS[i] = NULL;
    }

    irqInit(isrDefault);
}

extern void irqInitMinimal(IrqHandlerFn *handler)
{
    REG_IME = 0;

    ISR_MINIMAL_HANDLER = handler;

    irqInit(isrMinimal);
}

extern bool irqHandlerSet(uint16_t irq, IrqHandlerFn *fn)
{
    if (!irq || (irq & (irq - 1)))
    {
        return false;
    }

    ISR_DEFAULT_HANDLERS[(uint32_t)(0x09AF0000 * irq) >> 28] = fn;

    return true;
}

extern bool irqHandlerGet(uint16_t irq, IrqHandlerFn **fn)
{
    if (!irq || (irq & (irq - 1)))
    {
        return false;
    }

    *fn = ISR_DEFAULT_HANDLERS[(uint32_t)(0x09AF0000 * irq) >> 28];

    return true;
}

extern bool irqHandlerSwap(uint16_t irq, IrqHandlerFn **fn)
{
    if (!irq || (irq & (irq - 1)))
    {
        return false;
    }

    uint32_t idx = (uint32_t)(0x09AF0000 * irq) >> 28;

    IrqHandlerFn *p = ISR_DEFAULT_HANDLERS[idx];
    ISR_DEFAULT_HANDLERS[idx] = *fn;
    *fn = p;

    return true;
}

extern uint16_t irqEnable(uint16_t irqs)
{
    uint32_t ime = REG_IME;
    REG_IME = 0;

    uint16_t old = REG_IE;
    REG_IE = old | irqs;

    REG_IME = ime;

    return old;
}

extern uint16_t irqDisable(uint16_t irqs)
{
    uint32_t ime = REG_IME;
    REG_IME = 0;

    uint16_t old = REG_IE;
    REG_IE = old & ~irqs;

    REG_IME = ime;

    return old;
}

extern void irqFree(void (*f)(void *), void *arg)
{
    uint32_t ime = REG_IME;
    REG_IME = 0;

    f(arg);

    REG_IME = ime;
}

_LIBSEVEN_TARGET_ARM extern void irqMask(void)
{
    __asm__ volatile
    (
        "mrs r0, cpsr\n"
        "orr r0, r0, 0x80\n"
        "msr cpsr_c, r0\n"
        ::: "r0"
    );
}

_LIBSEVEN_TARGET_ARM extern void irqUnmask(void)
{
    __asm__ volatile
    (
        "mrs r0, cpsr\n"
        "bic r0, r0, 0x80\n"
        "msr cpsr_c, r0\n"
        ::: "r0"
    );
}

_LIBSEVEN_TARGET_ARM extern bool irqMasked(void)
{
    bool masked;

    __asm__ volatile
    (
        "mrs %0, cpsr\n"
        "lsr %0, %0, 7\n"
        "and %0, %0, 1\n"
        : "=r"(masked)
    );

    return masked;
}
