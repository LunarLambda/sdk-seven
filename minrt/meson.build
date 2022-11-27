version = '0.2.0'

sources = [
  'src/gba/rom_header.s',
  'src/gba/crt0.s',
  'src/gba/ram.c',
]

sources_mb = [
  'src/gba/multiboot_header.s',
  'src/gba/crt0.s',
  'src/gba/ram.c',
]

includes = ['include']

lib = meson.current_source_dir() / 'lib'

link_args = ['-specs=' + lib / 'nocrt0.specs', '-L' + lib / 'ldscripts']

minrt = static_library(
  'minrt_rom',
  sources,
  include_directories: includes + 'src' + 'src/gba',
  install: true)

minrt_mb = static_library(
  'minrt_mb',
  sources_mb,
  include_directories: includes + 'src' + 'src/gba',
  install: true)

install_headers('include/minrt.h')

libdata = [
  'lib/ldscripts/gba_base.ld',
  'lib/ldscripts/multiboot.ld',
  'lib/ldscripts/rom.ld',
  'lib/ldscripts/rom_alt_wram.ld',
  'lib/nocrt0.specs',
]

install_data(libdata, install_dir: get_option('libdir'))

minrt_dep = declare_dependency(
  include_directories: includes,
  link_with: minrt,
  link_args: link_args + '-Trom.ld',
  version: version)

minrt_mb_dep = declare_dependency(
  include_directories: includes,
  link_with: minrt_mb,
  link_args: link_args + '-Tmultiboot.ld',
  version: version)

meson.override_dependency('minrt', minrt_dep)
meson.override_dependency('minrt-multiboot', minrt_mb_dep)
