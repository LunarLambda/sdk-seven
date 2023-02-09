#include <stddef.h>

extern void (*__fini_array_start []) (void) __attribute__((weak));
extern void (*__fini_array_end []) (void) __attribute__((weak));

extern void __libc_fini_array(void)
{
    size_t count;
    size_t i;

    count = __fini_array_end - __fini_array_start;

    for (i = count; i > 0; i--)
    {
        __fini_array_start[i-1]();
    }
}
