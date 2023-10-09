project('sdk-seven', 'c',
  version: '0.27.1',
  license: 'Zlib',
  meson_version: '>=0.59.0',
  default_options: ['warning_level=2', 'c_std=c99'])

libseven_version = '0.22.2'
minrt_version = '0.9.0'
libutil_version = '0.2.0'

if not meson.is_subproject()
  subdir('meson/toolchain')
endif

subdir('libseven')
subdir('minrt')
subdir('libutil')
subdir('tools')

if not meson.is_subproject()
  subdir('examples')
endif
