project('sdk-seven', 'c',
  version: '0.1.1',
  license: 'Zlib',
  meson_version: '>=0.56.0')

add_project_arguments(
  '-mthumb',
  '-ffunction-sections',
  '-fdata-sections',
  language: 'c')

add_project_link_arguments(
  '-mthumb',
  '-Wl,--gc-sections',
  language: 'c')

subproject('libseven')
subproject('minrt')

subdir('tools')

mapfile = '-Wl,-Map,@0@.map'

if not meson.is_subproject()
  subdir('examples')
endif
