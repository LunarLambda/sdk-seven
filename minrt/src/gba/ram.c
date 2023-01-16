#include <stdint.h>
#include <minrt.h>

extern char __load;
extern char __load_end;
extern char __iwram_end;
extern char __ewram_end;
extern char __sp_sys;

size_t minrt_used_static_iwram(void)
{
    return (size_t)&__iwram_end - 0x03000000;
}

size_t minrt_used_static_ewram(void)
{
    return (size_t)&__ewram_end - 0x02000000;
}

size_t minrt_rom_size(void)
{
    return (size_t)&__load_end - (size_t)&__load;
}

size_t minrt_used_stack(void)
{
    uintptr_t sp;

    __asm__("mov %0, sp" : "=r"(sp));

    return (uintptr_t)&__sp_sys - sp;
}
