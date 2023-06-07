project('sdk-seven', 'c',
  version: '0.22.0',
  license: 'Zlib',
  meson_version: '>=0.59.0',
  default_options: ['warning_level=2', 'c_std=c99'])

libseven_version = '0.18.0'
minrt_version = '0.9.0'

cflags = [
  '-mthumb',
  '-ffunction-sections',
  '-fdata-sections',
  '-masm-syntax-unified'
]

ldflags = [
  '-mthumb',
  '-Wl,--gc-sections',
  '-Wl,-z,max-page-size=1'
]

# Generate debug info compatible with no$gba v3.05
#
# This does not work if libc or other system code is built with newer debug info
if get_option('debug')
  cflags += '-gdwarf-4'
endif

cc = meson.get_compiler('c')

# devkitARM has nano.specs, but no libc_nano
#
has_nano = cc.find_library('c_nano', required: false).found()

if get_option('use_nano').require(has_nano).allowed()
  ldflags += '-specs=nano.specs'
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
  ldflags += '-Wl,--no-warn-rwx-segments'
endif

add_project_arguments(cflags, language: 'c')
add_project_link_arguments(ldflags, language: 'c')

subdir('libseven')
subdir('minrt')
subdir('tools')

if not meson.is_subproject()
  subdir('examples')
endif
