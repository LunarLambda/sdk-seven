#include <stdint.h>
#include <minrt.h>

extern char __iwram_size;
extern char __ewram_size;

size_t minrt_used_static_iwram(void)
{
    return (size_t)&__iwram_size;
}

size_t minrt_used_static_ewram(void)
{
    return (size_t)&__ewram_size;
}

size_t minrt_used_stack(void)
{
    uintptr_t sp;

    __asm__("mov %0, sp" : "=r"(sp));

    return 0x03007F00 - sp;
}

ptrdiff_t minrt_stack_left(void)
{
    intptr_t sp;

    __asm__("mov %0, sp" : "=r"(sp));

    return sp - ((intptr_t)&__iwram_size + 0x03000000);
}
