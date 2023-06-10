sources = [
  'src/assert.c',
  'src/bit.s',
  'src/debug.s',
  'src/log.c',
  'src/mem.s',
  'src/profile.s',
  'src/rand.s',
  'src/simd.s',
  'src/str.s',
]

includes = ['include']

libutil = static_library(
  'util',
  sources,
  include_directories: includes + ['src'],
  dependencies: [libseven_dep],
  install: true)

install_subdir('include/util', install_dir: get_option('includedir'))

libutil_dep = declare_dependency(
  include_directories: includes,
  link_with: libutil,
  version: libutil_version)

meson.override_dependency('libutil', libutil_dep)
