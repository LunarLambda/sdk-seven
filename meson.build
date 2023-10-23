project('sdk-seven', 'c',
  version: '0.28.0',
  license: 'Zlib',
  meson_version: '>=0.64.0',
  default_options: ['warning_level=2', 'c_std=c99'])

libseven_version = '0.22.2'
minrt_version = '0.10.0'
libutil_version = '0.2.0'

if not meson.is_subproject()
  subdir('meson/toolchain')
else
  add_project_arguments('-masm-syntax-unified', language: 'c')
endif

subdir('minrt')
subdir('tools')

if not get_option('no_libs')
  subdir('libseven')
  subdir('libutil')

  if not meson.is_subproject()
    subdir('examples')
  endif
endif
