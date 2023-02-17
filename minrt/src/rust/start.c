extern int main(int, char **, char **);

extern void _start_lang(void)
{
    char *v[2] = {0};

    main(0, &v[0], &v[1]);
}
