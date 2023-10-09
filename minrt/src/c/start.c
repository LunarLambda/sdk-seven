#include <stdlib.h>

extern void __libc_init_array(void);

// Declare main without a prototype. Prevents LTO type warnings.
// Technically UB but so is picking one signature and the user picking another.
extern int main();

extern void _lang_start(void)
{
    __libc_init_array();

    char *v[2] = {0};

    // Prevent LTO from inling main()
    __asm__(""::"X"(main));

    exit(main(0, &v[0], &v[1]));
}
