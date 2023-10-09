#!/bin/sh
meson setup --cross-file=meson/arm-none-eabi.ini --cross-file=meson/arm7tdmi.ini "${1:-build}"
