objcopy = find_program('objcopy')

gbafix = find_program('src/gbafix.py')
bin2s = find_program('src/bin2s.py')

makerom = configure_file(
  input: 'src/makerom.py.in',
  output: 'makerom.py',
  configuration: {
    'OBJCOPY': objcopy.full_path(),
    'GBAFIX': gbafix.full_path(),
  })

# Workaround https://github.com/mesonbuild/meson/issues/11255
makerom = find_program(makerom)

meson.override_find_program('makerom', makerom)
meson.override_find_program('gbafix-py', gbafix)
meson.override_find_program('bin2s-py', bin2s)
