objcopy = find_program('objcopy')

gbafix = meson.current_source_dir() / 'src/gbafix.py'

makerom = configure_file(
  input: 'makerom.in',
  output: 'makerom',
  configuration: {
    'OBJCOPY': objcopy.full_path(),
    'GBAFIX': gbafix,
  })

meson.override_find_program('makerom', makerom)
