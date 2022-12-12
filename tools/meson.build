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

meson.override_find_program('makerom', makerom)
