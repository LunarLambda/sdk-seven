project('libseven', 'c',
  version: '0.7.1',
  license: 'MPL-2.0',
  default_options: ['warning_level=2', 'c_std=c99'])

sources = [
  'src/hw/dma.s',
  'src/hw/input.s',
  'src/hw/irq.s',
  'src/hw/sram.s',
  'src/hw/svc.s',
  'src/hw/timer.s',
  'src/util/debug.s',
  'src/util/log.c',
  'src/util/mem.s',
  'src/util/profile.s',
  'src/util/rand.s',
  'src/util/simd.s',
  'src/util/str.s',
  'src/video/bmp.s',
  'src/video/oam.s',
]

includes = ['include']

libseven = static_library(
  'seven',
  sources,
  include_directories: includes + 'src',
  c_args: ['-mthumb', '-ffunction-sections', '-fdata-sections', '-ffreestanding'])

libseven_dep = declare_dependency(
  include_directories: includes,
  link_with: libseven)

meson.override_dependency('libseven', libseven_dep)
