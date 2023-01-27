project('sdk-seven', 'c',
  version: '0.14.1',
  license: 'Zlib',
  meson_version: '>=0.55.0',
  default_options: ['warning_level=2', 'c_std=c99'])

add_project_arguments(
  '-mthumb',
  '-ffunction-sections',
  '-fdata-sections',
  language: 'c')

add_project_link_arguments(
  '-mthumb',
  '-Wl,--gc-sections',
  '-Wl,-z,max-page-size=1',
  language: 'c')

# Generate debug info compatible with no$gba v3.05
#
# This does not work if libc or other system code is built with newer debug info
if get_option('debug')
  add_project_arguments('-gdwarf-4', language: 'c')
endif

cc = meson.get_compiler('c')

# devkitARM has nano.specs, but no libc_nano
#
if cc.find_library('c_nano', required: false).found()
  add_project_link_arguments('-specs=nano.specs', language: 'c')
endif

# Remove warnings on newer toolchains
#
# Different toolchains are quite badly behaved, making meson's usual tests
# fail spuriously.
#
# So we just ask ld directly. Meson uses a variant of this (-Wl,--version)
# to detect the version of ld used by the compiler.
ld_h = run_command(cc, '-Wl,--help', capture: true, check: false)

if ld_h.stdout().contains('--no-warn-rwx-segments')
  add_project_link_arguments('-Wl,--no-warn-rwx-segments', language: 'c')
endif

subdir('libseven')
subdir('minrt')
subdir('tools')

if not meson.is_subproject()
  subdir('examples')
endif
