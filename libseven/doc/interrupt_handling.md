# Interrupt Handling

Reacting to hardware events such as display blanking intervals or timer
overflows involves the use of CPU interrupt requests, or IRQs.

An interrupt occurs when the nIRQ pin on the CPU is pulled low, and interrupts
are not masked by the CPU. Interrupt masking can be controlled via bit 7 of
the Current Program Status Register (CPSR).

Additionally, the GBA provides 3 I/O registers for controlling whether the CPU
receives an interrupt signal or not.

- `IME` (Interrupt Master Enable)
- `IE` (Interrupt Enable)
- `IF` (Interrupt Flag)

An interrupt signal is sent to the CPU if `IME` is set to 1 and an interrupt
is both enabled (in `IE`) and flagged (in `IF`). `IME` and `IE` are controlled
by the programmer, and `IF` is controlled by the hardware.

Enabling an interrupt in `IE` is not enough. The interrupt will only be
flagged (appear in `IF`) if the interrupt request is also enabled in the
appropriate hardware register. For example, receiving a vertical blank
interrupt requires the following configuration:

- `IME` is 1
- Bit 0 of `IE` is set
- Bit 3 of `DISPSTAT` is set

Once an interrupt is flagged in `IF`, it will stay flagged until the
programmer clears the flag by writing the corresponding bits to `IF`. This is
called "acknowledging" the interrupt. If an interrupt is not acknowledged, it
will be triggered again if conditions allow it.

When modifying `IE`, it is recommended to set `IME` to 0 first, so that
modifications behave atomically, meaning an interrupt cannot change `IE` while
the main program is trying to do so, and a temporary value in `IE` cannot
trigger an unwanted interrupt.

## Interrupt Sources

This table lists the different interrupt sources, as well as the matching bits
in `IE`/`IF` and the appropriate hardware registers.

Source                                           | IE/IF  | I/O
-------------------------------------------------|--------|------------------
Display entered vertical blank                   | Bit 0  | Bit 3 in `DISPSTAT`
Display entered horizontal blank                 | Bit 1  | Bit 4 in `DISPSTAT`
Display vertical counter match                   | Bit 2  | Bit 5 in `DISPSTAT`
Timer 0 overflowed                               | Bit 3  | Bit 6 in `TM0CNT`
Timer 1 overflowed                               | Bit 4  | Bit 6 in `TM1CNT`
Timer 2 overflowed                               | Bit 5  | Bit 6 in `TM2CNT`
Timer 3 overflowed                               | Bit 6  | Bit 6 in `TM3CNT`
Serial Normal / Multi / UART: transfer completed | Bit 7  | Bit 14 in `SIOCNT`
Serial JOY BUS: device reset received            | Bit 7  | Bit 6 in `JOYCNT`
Serial GPIO: SI pulled low                       | Bit 7  | Bit 8 in `RCNT`
DMA 0 completed                                  | Bit 8  | Bit 14 in `DMA0CNT`
DMA 1 completed                                  | Bit 9  | Bit 14 in `DMA1CNT`
DMA 2 completed                                  | Bit 10 | Bit 14 in `DMA2CNT`
DMA 3 completed                                  | Bit 11 | Bit 14 in `DMA3CNT`
Keypad combination pressed                       | Bit 12 | Bit 14 in `KEYCNT`
Cartridge interrupt request                      | Bit 13 | N/A

## Interrupt Vector

When an interrupt is triggered, the CPU switches into IRQ mode and jumps to
the interrupt vector located at address `0000 0018`. At this point, interrupts
are masked via the CPSR. From there it jumps to the following sequence of
instructions:

```arm
push    {r0-r3, r12, lr}
mov     r0, 0x04000000
add     lr, pc, 0
ldr     pc, [r0, -4]
pop     {r0-r3, r12, lr}
subs    pc, lr, 4
```

This sequence branches to the address stored at `03FF FFFC`. The called
function must use ARM code, and can freely use the registers `r0`, `r1`, `r2`,
`r3`, and `r12`. `r0` will always contain the address `0400 0000`.

## IntrWait

The BIOS provides a special function called `IntrWait`. It puts the CPU into a
low-power sleep state until the requested interrupt occurs. It always sets
`IME` to 1. Notably, this function does *not* use `IF` to check whether the
interrupt was acknowledged or not. Instead, it uses a variable located in RAM
at address `03FF FFF8`. This variable is also referred to as `IFBIOS`, due to
its similarity to the `IF` register. Because it is a regular RAM location,
acknowledging interrupts should be done using a logical OR operation, instead
of writing the bits directly.

## Interrupt Service Routine

The function address stored at `03FF FFFC` is called the interrupt service
routine (ISR), or sometimes just "interrupt handler", although that name is
ambiguous.

The ISR generally has the following tasks:

- Find the source of the interrupt by checking which of the enabled interrupts
  was flagged
- Acknowledge the interrupt
- Perform any additional bookkeeping duties (saving registers, switching
  modes, etc.)
- Optionally delegate to another handler function, for example to use THUMB
  code
- Return to the BIOS

The bare minimum pseudocode for an ISR looks like this:

```
irqs = IE & IF
IF = irqs
IFBIOS |= irqs
return
```

While not strictly necessary, it is common to write ISRs in assembly.
Optimized, the above code looks like this:

```arm
ldr     r1, [r0, 0x200]!    @ Read IE and IF into a single register
and     r1, r1, r1, lsr 16  @ Compute IE & IF
strh    r1, [r0, 2]         @ Acknowledge interrupts in IF
ldr     r2, [r0, -0x208]!   @ \
orr     r2, r2, r1          @  > Acknowledge interrupts in IFBIOS
strh    r2, [r0], 8         @ /
bx      lr                  @ Return to BIOS
```

Note that this routine provides no additional functionality besides making the
`IntrWait` function work. Note also that if multiple interrupts occur in close
proximity to each other, the ISR will acknowledge both. Depending on how the
ISR is set up, this may or may not be desirable. Always make sure to only
acknowledge interrupts you actually handled.

### Nesting

Generally, while the ISR is running, further interrupts cannot occur. They
will be delayed until either the ISR unmasks interrupts in the CPSR, or the
ISR returns to the BIOS, at which point the previous CPSR value is restored.

However, sometimes it can be beneficial to allow nesting, such that an
interrupt with high priority can occur while an interrupt with low priority is
being handled.

Nesting can be enabled in a variety of ways, such as saving `IME` and setting
it to 0 before unmasking interrupts, such that a handler function can opt into
nesting by setting `IME` to 1 again, or by keeping `IME` set to 1 and letting
the handler function unmask interrupts itself, or by enabling nesting
unconditionally and using a priority system to test if the interrupt should be
given priority or delayed.

In any case, because an interrupt always causes a mode switch in the CPU, it
is required to save the Saved Program Status Register (SPSR) before enabling
nesting. This is important because the SPSR stores the CPSR at the time the
interrupt occured, and is restored when the ISR returns, so it must be
preserved correctly.

## Memory Safety

Even if the CPU can only ever truly execute one instruction at a time,
semantically speaking, an interrupt occuring is equivalent to a new thread of
execution starting. This means that care must be taken when accessing global
state (such as RAM variables, or I/O registers) to make sure that invalid data
isn't accessed or temporary values are not destroyed.

There are a few ways to ensure this, such as to never share global state
between interrupts and main code, or if necessary, to make data access
unidirectional, meaning that interrupts only write certain variables, and main
code only reads them, or vice versa, or to disable interrupts before accessing
critical data, or to use DMA transfers, since they pause the CPU entirely.
