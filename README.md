# sdk-seven — Modern GBA SDK

sdk-seven provides all the necessary components for building software for the
Game Boy Advance. It is built from scratch with an emphasis on correctness and
performance. While still in active development, the core components have proven
quite solid already.

It includes the following components:

- libseven, a development library for interacting with the GBA hardware
- minrt, a runtime library for building and running GBA ROMs
- Python helper scripts

## Requires

- meson >=0.59.0
- arm-none-eabi toolchain (gcc, binutils, newlib)

## Setup

```
./meson-setup.sh
ninja -C build
```

## Support

Development of sdk-seven and other GBA homebrew projects can be supported
through [Patreon](https://patreon.com/LunarLambda).

You can also reach out to us in the `#sdk-seven` channel in the
[gbadev Discord](https://discord.io/gbadev).

## Licenses

sdk-seven is licensed under the Zlib License, with the following exceptions:

libseven and minrt are licensed under the Mozilla Public License Version 2.0.\
Documentation is licensed under the CC0 1.0 Universal License.
