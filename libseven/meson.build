sources = [
  'src/hw/bios.c',
  'src/hw/bios.s',
  'src/hw/dma.s',
  'src/hw/input.c',
  'src/hw/irq.c',
  'src/hw/isr.s',
  'src/hw/sram.s',
  'src/hw/timer.c',
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
  version: libseven_version)

meson.override_dependency('libseven', libseven_dep)
