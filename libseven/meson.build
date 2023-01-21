version = '0.14.0'

sources = [
  'src/hw/bios.s',
  'src/hw/dma.s',
  'src/hw/input.c',
  'src/hw/irq.c',
  'src/hw/isr.s',
  'src/hw/sram.s',
  'src/hw/timer.s',
  'src/util/assert.c',
  'src/util/bit.s',
  'src/util/debug.s',
  'src/util/log.c',
  'src/util/mem.s',
  'src/util/profile.s',
  'src/util/rand.s',
  'src/util/simd.s',
  'src/util/str.s',
  'src/video/oam.s',
]

includes = ['include']

libseven = static_library(
  'seven',
  sources,
  include_directories: includes + ['src'],
  install: true)

install_subdir('include/seven', install_dir: get_option('includedir'))

libseven_dep = declare_dependency(
  include_directories: includes,
  link_with: libseven,
  version: version)

meson.override_dependency('libseven', libseven_dep)
