#include <stdlib.h>

extern void __libc_init_array(void);
extern int main(int, char **, char **);

extern void _start_lang(void)
{
    char *v[2] = {0};

    __libc_init_array();

    exit(main(0, &v[0], &v[1]));
}
