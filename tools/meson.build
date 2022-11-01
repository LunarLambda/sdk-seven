objcopy = find_program('objcopy')

gbafix = executable('gbafix', 'gbafix.c', native: true)

makerom = configure_file(
  input: 'makerom.in',
  output: 'makerom',
  configuration: {
    'OBJCOPY': objcopy.full_path(),
    'GBAFIX': gbafix.full_path(),
  })
