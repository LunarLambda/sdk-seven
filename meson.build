project('sdk-seven', 'c',
  version: '0.3.0',
  license: 'Zlib',
  meson_version: '>=0.60.0',
  default_options: ['warning_level=2', 'c_std=c99'])

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

subdir('libseven')
subdir('minrt')

subdir('tools')

mapfile = '-Wl,-Map,@0@.map'

if not meson.is_subproject()
  subdir('examples')
endif
