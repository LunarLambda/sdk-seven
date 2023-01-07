objcopy = find_program('objcopy')

gbafix = meson.current_source_dir() / 'src/gbafix.py'

makerom = configure_file(
  input: 'src/makerom.py.in',
  output: 'makerom.py',
  configuration: {
    'OBJCOPY': objcopy.full_path(),
    'GBAFIX': gbafix,
  })

meson.override_find_program('makerom', makerom)
