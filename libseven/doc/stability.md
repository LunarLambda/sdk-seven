# Stability

Written for: libseven 0.13.0

Libseven is currently still in active development, and subject to many changes.
Some parts are considered mature, but a truly stable 1.0.0 release is still
a while away. This page aims to document the current state of libseven's APIs.

The information here comes without any guarantee of being or remaining true.

## Roadmap

Libseven follows semver, but due to the large amount of different, independent
modules, stability will be tiered.

### 1.0.0

Version 1.0.0, the following modules will be considered stable, and subject to
the proper semantic versioning rules:

- `<seven/base.h>`
- `<seven/prelude.h>`
- `<seven/hw/bios.h>`
- `<seven/hw/dma.h>`
- `<seven/hw/input.h>`
- `<seven/hw/irq.h>`
- `<seven/hw/memory.h>`
- `<seven/hw/timer.h>`
- `<seven/hw/video.h>`
- `<seven/hw/waitstate.h>`

Everything else will continue to be subject to pre-1.0 rules.

### 2.0.0

Version 2.0.0 will fully stabilize the following:

- `<seven/hw/bios/*>`
- `<seven/hw/serial.h>`
- `<seven/hw/sram.h>`
- `<seven/hw/video/*>`

### 3.0.0 Onwards

There are no concrete plans for version 3.0.0 and beyond, though the general
focus will be the serial I/O and sound APIs.

There is no roadmap for the utility headers, as they may be factored out into
their own library entirely.

## Stable

These modules are considered stable, meaning they should not be subject to
breaking changes until 1.0.0.

- `<seven/hw/bios.h>`
- `<seven/hw/dma.h>`
- `<seven/hw/input.h>`
- `<seven/hw/irq.h>`
- `<seven/hw/memory.h>`

## Stable, But...

These modules are considered stable, but shouldn't be relied on too strongly:

- The `<seven/prelude.h>` and any other 'prelude' headers
- The `<seven/base/*>` headers

## Stable-ish

These modules may receive minor breaking changes,
such as naming or content changes.

- The `<seven/hw/bios/*>` headers
- `<seven/hw/timer.h>`
- `<seven/hw/video.h>`
- `<seven/hw/waitstate.h>`

## Unstable

These modules may receive major breaking changes,
such as significant rewrites, or deletion.

- `<seven/hw/cartridge.h>`
- `<seven/hw/cpu.h>`
- `<seven/hw/serial.h>`
- `<seven/hw/sram.h>`
- The `<seven/hw/video/*>` headers
- The `<seven/util/*>` headers

## Unimplemented

These modules are not yet usable, but are present for organisational purposes:

- `<seven/hw/sound.h>`
- The `<seven/hw/serial/*>` headers
- `<seven/hw/video/palette.h>`
