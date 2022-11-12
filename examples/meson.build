subdir('template')
subdir('vsync')
subdir('vsync-callback')

elfs = [
  example_template,
  example_vsync,
  example_vsync_callback,
]

foreach bin : elfs
  custom_target(
    bin.name() + '-rom',
    input: bin,
    output: bin.name() + '.gba',
    command: [makerom, '@INPUT@', '@OUTPUT@'],
    # https://github.com/mesonbuild/meson/discussions/10981#discussioncomment-4034259
    depends: [gbafix],
    build_by_default: true)
endforeach
