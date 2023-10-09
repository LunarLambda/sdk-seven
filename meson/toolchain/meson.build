# List of global compiler arguments.
compile_args = [
  '-ffunction-sections',        # Every function gets placed into its own section.
  '-fdata-sections',            # Every global variable gets placed into its own section.
  '-mthumb',                    # Generate THUMB code by default.
  '-masm-syntax-unified',       # Use unified assembler syntax for inline assembly.
]

if get_option('debug')
  compile_args += [
    '-g3',                      # Generate extended debug information for macros.
    '-gdwarf-4'                 # no$gba does not support DWARF 5 debug info and crashes.
  ]
endif

add_project_arguments(compile_args, language: ['c', 'cpp'])

cc = meson.get_compiler('c')

# List of link arguments.
link_args = [
  '-mthumb',                    # Link with THUMB builds of libraries like libc
  '-Wl,-n',                     # Get rid of section page alignment. Reduces ELF file size.
  '-Wl,--gc-sections',          # Remove unused sections.
  '-Wl,-Map=%',                 # Generate a link map file.
]

# Newer binutils add warnings we don't care about.
ld_h = run_command(cc, '-Wl,--help', capture: true, check: false)

if ld_h.stdout().contains('--no-warn-rwx-segments')
  link_args += '-Wl,--no-warn-rwx-segments'
endif

# Use libc_nano if available.
if cc.find_library('c_nano', required: false).found()
  link_args += '-specs=nano.specs'
endif

add_project_link_arguments(link_args, language: ['c', 'cpp'])
