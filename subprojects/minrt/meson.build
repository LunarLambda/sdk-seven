project('minrt', 'c',
  version: '0.1.1',
  license: 'MPL-2.0',
  default_options: ['warning_level=2', 'c_std=c99'])

sources = [
  'src/crt0.s',
  'src/ram.c',
]

includes = ['include']

lib = meson.project_source_root() / 'lib'

link_args = ['-specs=' + lib / 'nocrt0.specs', '-L' + lib]

minrt = static_library(
  'minrt',
  sources,
  include_directories: includes + 'src',
  c_args: ['-mthumb', '-ffunction-sections', '-fdata-sections', '-ffreestanding'])

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
