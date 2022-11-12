project('sdk-seven', 'c',
  version: '0.2.0',
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
  '-specs=nosys.specs',
  language: 'c')

cc = meson.get_compiler('c')

# Detect newlib-nano
#
if cc.has_argument('-specs=nano.specs')
  add_project_link_arguments(
    '-specs=nano.specs',
    language: 'c')
endif

subproject('libseven')
subproject('minrt')

subdir('tools')

mapfile = '-Wl,-Map,@0@.map'

if not meson.is_subproject()
  subdir('examples')
endif
