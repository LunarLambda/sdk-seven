version = '0.9.0'

sources = [
  'src/hw/dma.s',
  'src/hw/input.s',
  'src/hw/irq.s',
  'src/hw/sram.s',
  'src/hw/svc.s',
  'src/hw/timer.s',
  'src/util/bit.s',
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
  include_directories: includes + 'src')

libseven_dep = declare_dependency(
  include_directories: includes,
  link_with: libseven,
  version: version)

meson.override_dependency('libseven', libseven_dep)
