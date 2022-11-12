project('minrt', 'c',
  version: '0.2.0',
  license: 'MPL-2.0',
  default_options: ['warning_level=2', 'c_std=c99'])

sources = [
  'src/gba/rom_header.s',
  'src/gba/crt0.s',
  'src/gba/ram.c',
]

includes = ['include']

lib = meson.project_source_root() / 'lib'

link_args = ['-specs=' + lib / 'nocrt0.specs', '-L' + lib / 'ldscripts']

minrt = static_library(
  'minrt',
  sources,
  include_directories: includes + 'src' + 'src/gba',
  c_args: ['-mthumb', '-ffunction-sections', '-fdata-sections'])

minrt_dep = declare_dependency(
  include_directories: includes,
  link_with: minrt,
  link_args: link_args + '-Trom.ld')

minrt_mb_dep = declare_dependency(
  include_directories: includes,
  link_with: minrt,
  link_args: link_args + '-Tmultiboot.ld')

meson.override_dependency('minrt', minrt_dep)
meson.override_dependency('minrt-multiboot', minrt_mb_dep)
