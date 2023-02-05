/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

// Attribute for compiling functions in a way that is suitable for ISRs.
//
#define ISR_FUNCTION    IWRAM_CODE ARM_CODE

// Interrupt Enable
//
#define REG_IE          VOLADDR(0x04000200, uint16_t)

// Interrupt Flags
//
#define REG_IF          VOLADDR(0x04000202, uint16_t)

// Interrupt Master Enable
//
#define REG_IME         VOLADDR(0x04000208, uint16_t)

// Interrupt Service Routine Function Pointer
//
#define MEM_ISR         MEMADDR(0x03FFFFFC, IsrFn*)

// IRQ bitflags
//
enum IRQ
{
    IRQ_VBLANK          = BIT(0),
    IRQ_HBLANK          = BIT(1),
    IRQ_VCOUNT          = BIT(2),
    IRQ_TIMER_0         = BIT(3),
    IRQ_TIMER_1         = BIT(4),
    IRQ_TIMER_2         = BIT(5),
    IRQ_TIMER_3         = BIT(6),
    IRQ_SERIAL          = BIT(7),
    IRQ_DMA_0           = BIT(8),
    IRQ_DMA_1           = BIT(9),
    IRQ_DMA_2           = BIT(10),
    IRQ_DMA_3           = BIT(11),
    IRQ_KEYPAD          = BIT(12),
    IRQ_CARTRIDGE       = BIT(13),
};

// Common sets of IRQs
//
enum IRQGroup
{
    IRQS_BLANK          = IRQ_VBLANK  | IRQ_HBLANK,
    IRQS_TIMER          = IRQ_TIMER_0 | IRQ_TIMER_1 | IRQ_TIMER_2 | IRQ_TIMER_3,
    IRQS_DMA            = IRQ_DMA_0   | IRQ_DMA_1   | IRQ_DMA_2   | IRQ_DMA_3,
    // IRQs in this group can wake up the GBA from a svcStop() call.
    IRQS_EXTERNAL       = IRQ_SERIAL  | IRQ_KEYPAD  | IRQ_CARTRIDGE,
    IRQS_ALL            = BITS(14),
};

// Bit indices of IRQs
enum IRQIndex
{
    IRQ_INDEX_VBLANK,
    IRQ_INDEX_HBLANK,
    IRQ_INDEX_VCOUNT,
    IRQ_INDEX_TIMER_0,
    IRQ_INDEX_TIMER_1,
    IRQ_INDEX_TIMER_2,
    IRQ_INDEX_TIMER_3,
    IRQ_INDEX_SERIAL,
    IRQ_INDEX_DMA_0,
    IRQ_INDEX_DMA_1,
    IRQ_INDEX_DMA_2,
    IRQ_INDEX_DMA_3,
    IRQ_INDEX_KEYPAD,
    IRQ_INDEX_CARTRIDGE,
    IRQ_INDEX_MAX,
};

// Function type for interrupt service routines (ISRs)
//
// Function must be ARM code, and ideally be placed in IWRAM.
//
// Use the ISR_FUNCTION attribute to mark the function appropriately.
typedef void IsrFn(void);

// Function type for interrupt callbacks.
//
// The function receives the triggered IRQs as the first parameter.
typedef void IrqHandlerFn(uint16_t);

// Initialize interrupt handling with a user-provided function.
//
extern void irqInit(IsrFn *isr);

// Initialize interrupt handling using a handler system.
//
// Used with the irqHandler* functions.
extern void irqInitDefault(void);

// Initialize interrupt handling using a single handler function.
//
extern void irqInitSimple(IrqHandlerFn *fn);

// Initialize interrupt handling using a stub handler
// that only acknowledges the IRQs and returns.
//
// This is enough for the BIOS interrupt wait functions to work.
extern void irqInitStub(void);

// Set the handler associated with the specified irq.
//
// Fails if irq specifies more than one interrupt.
extern bool irqHandlerSet(uint16_t irq, IrqHandlerFn *fn);

// Get the callback associated with the specified irq.
//
// Fails if irq specifies more than one interrupt.
extern bool irqHandlerGet(uint16_t irq, IrqHandlerFn **fn);

// Swap the handler associated with the specified irq, returning the old one.
//
// Fails if irq specifies more than one interrupt.
extern bool irqHandlerSwap(uint16_t, IrqHandlerFn **fn);

// Enable the specified IRQs.
//
// Returns the old value of the IE register.
extern uint16_t irqEnable(uint16_t irqs);

// Disable the specified IRQs.
//
// Returns the old value of the IE register.
extern uint16_t irqDisable(uint16_t irqs);

// Enable the specified IRQs and IRQ enable bits in the respective IO registers.
//
// Returns the old value of the IE register.
extern uint16_t irqEnableFull(uint16_t irqs);

// Disable the specified IRQs and IRQ enable bits in the respective IO registers.
//
// Returns the old value of the IE register.
extern uint16_t irqDisableFull(uint16_t irqs);

// Calls a function with IRQs disabled, passing data as an argument.
extern void irqFree(void (*f)(void*), void *arg);

_LIBSEVEN_EXTERN_C_END
