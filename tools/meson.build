objcopy = find_program('objcopy')

gbafix = executable('gbafix', 'gbafix.c', native: true)

makerom = configure_file(
  input: 'makerom.in',
  output: 'makerom.in',
  configuration: {
    'OBJCOPY': objcopy.full_path(),
    'GBAFIX': gbafix.full_path(),
  })

makerom = custom_target('makerom',
  input: makerom,
  output: 'makerom',
  command: ['copy', '@INPUT@', '@OUTPUT@'],
  depends: [gbafix],
  build_by_default: true)

# Broken: https://github.com/mesonbuild/meson/issues/11167#issuecomment-1356302184
# meson.override_find_program('makerom', files(makerom.full_path()))
