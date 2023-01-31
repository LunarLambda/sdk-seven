/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <seven/base.h>
#include <seven/hw/irq.h>

extern IsrFn isrDefault;
extern IsrFn isrSimple;
extern IsrFn isrStub;

extern IrqHandlerFn* ISR_SIMPLE_HANDLER;
extern IrqHandlerFn* ISR_DEFAULT_HANDLERS[16];

extern void irqInit(IsrFn *isr)
{
    REG_IME = 0;
    REG_IE = 0;
    REG_IF = 0xFFFF;

    MEM_ISR = isr;

    REG_IME = 1;
    return;
}

extern void irqInitDefault(void)
{
    REG_IME = 0;

    for (usize i = 0; i < 16; i++)
    {
        ISR_DEFAULT_HANDLERS[i] = NULL;
    }

    irqInit(isrDefault);
}

extern void irqInitSimple(IrqHandlerFn *handler)
{
    REG_IME = 0;

    ISR_SIMPLE_HANDLER = handler;

    irqInit(isrSimple);
}

extern void irqInitStub(void)
{
    irqInit(isrStub);
}

extern bool irqHandlerSet(u16 irq, IrqHandlerFn *fn)
{
    if (!irq || (irq & (irq - 1)))
    {
        return false;
    }

    ISR_DEFAULT_HANDLERS[(u32)(0x09AF0000 * irq) >> 28] = fn;

    return true;
}

extern bool irqHandlerGet(u16 irq, IrqHandlerFn **fn)
{
    if (!irq || (irq & (irq - 1)))
    {
        return false;
    }

    *fn = ISR_DEFAULT_HANDLERS[(u32)(0x09AF0000 * irq) >> 28];

    return true;
}

extern bool irqHandlerSwap(u16 irq, IrqHandlerFn **fn)
{
    if (!irq || (irq & (irq - 1)))
    {
        return false;
    }

    u32 idx = (u32)(0x09AF0000 * irq) >> 28;

    IrqHandlerFn *p = ISR_DEFAULT_HANDLERS[idx];
    ISR_DEFAULT_HANDLERS[idx] = *fn;
    *fn = p;

    return true;
}

extern u16 irqEnable(u16 irqs)
{
    u32 ime = REG_IME;
    REG_IME = 0;

    u16 old = REG_IE;
    REG_IE = old | irqs;

    REG_IME = ime;

    return old;
}

extern u16 irqDisable(u16 irqs)
{
    u32 ime = REG_IME;
    REG_IME = 0;

    u16 old = REG_IE;
    REG_IE = old & ~irqs;

    REG_IME = ime;

    return old;
}

extern void irqFree(void (*f)(void*), void *arg)
{
    u32 ime = REG_IME;
    REG_IME = 0;

    f(arg);

    REG_IME = ime;

    return;
}
