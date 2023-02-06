#include <stdlib.h>
#include <unistd.h>

extern void exit(int code)
{
    void __call_exitprocs(int, void*) __attribute__((weak));
    void __libc_fini_array(void);

    if (__call_exitprocs)
    {
        __call_exitprocs(code, NULL);
    }

    __libc_fini_array();

    _exit(code);
}
