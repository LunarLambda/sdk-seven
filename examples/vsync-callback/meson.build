example_vsync_callback = executable('example-vsync-callback', 'src/main.c',
  dependencies: [libseven, minrt],
  link_args: [mapfile.format('example-vsync-callback')],
  name_suffix: 'elf')

custom_target('example-vsync-callback-rom',
  input: example_vsync_callback,
  output: 'example-vsync-callback.gba',
  command: [makerom, '@INPUT@', '@OUTPUT@'],
  build_by_default: true)
