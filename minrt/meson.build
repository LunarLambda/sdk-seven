version = '0.7.0'

sources = [
  'src/gba/crt0.s',
  'src/gba/exit.c',
  'src/gba/fini.c',
  'src/gba/init.c',
  'src/gba/ram.c',
]

includes = ['include']

lib = meson.current_source_dir() / 'lib'

link_args = ['-specs=' + lib / 'nocrt0.specs', '-L' + lib / 'ldscripts']

minrt = static_library(
  'minrt_rom',
  sources + ['src/gba/rom_header.s'],
  include_directories: includes + ['src/gba'],
  install: true)

minrt_mb = static_library(
  'minrt_mb',
  sources + ['src/gba/multiboot_header.s'],
  include_directories: includes + ['src/gba'],
  install: true)

install_headers('include/minrt.h')

libdata = [
  'lib/ldscripts/gba.x',
  'lib/ldscripts/multiboot.mem',
  'lib/ldscripts/rom.mem',
  'lib/nocrt0.specs',
]

install_data(libdata, install_dir: get_option('libdir'))

minrt_dep = declare_dependency(
  include_directories: includes,
  link_with: minrt,
  link_args: link_args + ['-Trom.mem', '-Tgba.x'],
  version: version)

minrt_mb_dep = declare_dependency(
  include_directories: includes,
  link_with: minrt_mb,
  link_args: link_args + ['-Tmultiboot.mem', '-Tgba.x'],
  version: version)

meson.override_dependency('minrt', minrt_dep)
meson.override_dependency('minrt-multiboot', minrt_mb_dep)
