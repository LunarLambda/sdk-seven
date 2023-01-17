example_vsync = executable('example-vsync', 'src/main.c',
  dependencies: [libseven, minrt],
  link_args: [mapfile.format('example-vsync')],
  name_suffix: 'elf')

custom_target('example-vsync-rom',
  input: example_vsync,
  output: 'example-vsync.gba',
  command: [makerom, '@INPUT@', '@OUTPUT@'],
  build_by_default: true)
