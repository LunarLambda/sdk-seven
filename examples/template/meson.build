example_template = executable('example-template', 'src/main.c',
  dependencies: [libseven, minrt],
  link_args: [mapfile.format('example-template')],
  name_suffix: 'elf')

custom_target('example-template-rom',
  input: example_template,
  output: 'example-template.gba',
  command: [makerom, '@INPUT@', '@OUTPUT@'],
  build_by_default: true)
