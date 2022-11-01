project('minrt', 'c',
  version: '0.1.0',
  license: 'MPL-2.0')

sources = [
  'src/crt0.s',
  'src/ram.c',
]

include = ['include']

lib = meson.project_source_root() / 'lib'

link_args = ['-specs=' + lib / 'nocrt0.specs', '-L' + lib]

minrt = static_library(
  'minrt',
  sources,
  include_directories: include + 'src')

minrt_dep = declare_dependency(
  include_directories: include,
  link_with: minrt,
  link_args: link_args + '-Trom.ld')

minrt_mb_dep = declare_dependency(
  include_directories: include,
  link_with: minrt,
  link_args: link_args + '-Tmultiboot.ld')

meson.override_dependency('minrt', minrt_dep)
meson.override_dependency('minrt-multiboot', minrt_mb_dep)
