// mode-safe inline swi using assembler offset magic:
//
// swi N << ((1f - . == 4) * -16); 1:
//
// clobbers: r0, r1, r3, memory
// make sure to always set input operands as +r outputs because of clobbering
//
// use inline rather than static inline so fallback to asm'd definitions
// possible (for FFI and debug builds)
//
// __attribute__((target(...), noinline, section(...)) works with LTO too.
