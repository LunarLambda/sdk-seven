extern int main(int, char **, char **);

extern void _lang_start(void)
{
    char *v[2] = {0};

    // Prevent LTO from inlining main()
    __asm__(""::"X"(main));

    main(0, &v[0], &v[1]);
}
