objcopy = find_program('objcopy')

gbafix = meson.current_source_dir() / 'src/gbafix.py'
bin2s = meson.current_source_dir() / 'src/bin2s.py'

makerom = configure_file(
  input: 'src/makerom.py.in',
  output: 'makerom.py',
  configuration: {
    'OBJCOPY': objcopy.full_path(),
    'GBAFIX': gbafix,
  })

meson.override_find_program('makerom', makerom)
meson.override_find_program('gbafix-py', files(gbafix))
meson.override_find_program('bin2s-py', files(bin2s))
