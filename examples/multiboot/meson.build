example_multiboot = executable('example-multiboot', 'src/main.c',
  dependencies: [libseven, minrt],
  link_args: [mapfile.format('example-multiboot')],
  name_suffix: 'elf')

custom_target('example-multiboot-rom',
  input: example_multiboot,
  output: 'example-multiboot.gba',
  command: [makerom, '@INPUT@', '@OUTPUT@'],
  build_by_default: true)
