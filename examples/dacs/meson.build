example_template = executable('example-dacs', 'src/main.c',
  dependencies: [libseven, minrt],
  name_suffix: 'elf')

custom_target('example-dacs-rom',
  input: example_template,
  output: '@BASENAME@.gba',
  command: [makerom, '@INPUT@', '@OUTPUT@'],
  build_by_default: true)
