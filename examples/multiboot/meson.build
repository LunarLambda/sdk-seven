example_multiboot = executable('example-multiboot', 'src/main.c',
  dependencies: [dependency('libseven'), dependency('minrt-multiboot')],
  link_args: [mapfile.format('example-multiboot')],
  name_suffix: 'elf')
