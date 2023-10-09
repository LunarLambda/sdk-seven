# sdk-seven — Modern GBA SDK

sdk-seven provides all the necessary components for building software for the
Game Boy Advance. It is built from scratch with an emphasis on correctness and
performance. While still in active development, the core components have proven
quite solid already.

It includes the following components:

- libseven, a development library for interacting with the GBA hardware
- libutil, a small library of utility functions
- minrt, a runtime library for building and running GBA ROMs
- Python helper scripts

While generally aiming to provide optimized routines for many different aspects
of GBA programming, sdk-seven does not provide optimized memory or math functions.

Consider using [agbabi](https://github.com/felixjones/agbabi) for those.

[meson-gba](https://github.com/LunarLambda/meson-gba) makes it easy to use
sdk-seven and any number of additional libraries and tools.

[gba-toolchain](https://github.com/felixjones/gba-toolchain) provides similar
functionality, using Cmake.

## Requires

- meson >=0.59.0
- arm-none-eabi toolchain (gcc, binutils, newlib)

## Setup

```
./setup.sh
ninja -C build
```

Check `meson configure build` for available configuration options.

## Support

Development of sdk-seven and other GBA homebrew projects can be supported
through [Patreon](https://patreon.com/LunarLambda).

You can also reach out to us in the `#sdk-seven` channel in the
[gbadev Discord](https://discord.io/gbadev).

## Licenses

sdk-seven is licensed under the Zlib License, with the following exceptions:

libseven, minrt, and libutil are licensed under the Mozilla Public License Version 2.0.\
Documentation is licensed under the CC0 1.0 Universal License.
