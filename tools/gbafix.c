#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct GbaHeader
{
    uint32_t    entry;
    uint8_t     logo[156];
    char        title[12];
    char        game_code[4];
    char        maker_code[2];
    uint8_t     hex96;
    uint8_t     unit_code;
    uint8_t     device_type;
    uint8_t     reserved1[7];
    uint8_t     version;
    uint8_t     checksum;
    uint8_t     reserved2[2];
};

static const uint8_t NINTENDO_LOGO[156] =
{
    0x24, 0xFF, 0xAE, 0x51, 0x69, 0x9A, 0xA2, 0x21,
    0x3D, 0x84, 0x82, 0x0A, 0x84, 0xE4, 0x09, 0xAD,
    0x11, 0x24, 0x8B, 0x98, 0xC0, 0x81, 0x7F, 0x21,
    0xA3, 0x52, 0xBE, 0x19, 0x93, 0x09, 0xCE, 0x20,
    0x10, 0x46, 0x4A, 0x4A, 0xF8, 0x27, 0x31, 0xEC,
    0x58, 0xC7, 0xE8, 0x33, 0x82, 0xE3, 0xCE, 0xBF,
    0x85, 0xF4, 0xDF, 0x94, 0xCE, 0x4B, 0x09, 0xC1,
    0x94, 0x56, 0x8A, 0xC0, 0x13, 0x72, 0xA7, 0xFC,
    0x9F, 0x84, 0x4D, 0x73, 0xA3, 0xCA, 0x9A, 0x61,
    0x58, 0x97, 0xA3, 0x27, 0xFC, 0x03, 0x98, 0x76,
    0x23, 0x1D, 0xC7, 0x61, 0x03, 0x04, 0xAE, 0x56,
    0xBF, 0x38, 0x84, 0x00, 0x40, 0xA7, 0x0E, 0xFD,
    0xFF, 0x52, 0xFE, 0x03, 0x6F, 0x95, 0x30, 0xF1,
    0x97, 0xFB, 0xC0, 0x85, 0x60, 0xD6, 0x80, 0x25,
    0xA9, 0x63, 0xBE, 0x03, 0x01, 0x4E, 0x38, 0xE2,
    0xF9, 0xA2, 0x34, 0xFF, 0xBB, 0x3E, 0x03, 0x44,
    0x78, 0x00, 0x90, 0xCB, 0x88, 0x11, 0x3A, 0x94,
    0x65, 0xC0, 0x7C, 0x63, 0x87, 0xF0, 0x3C, 0xAF,
    0xD6, 0x25, 0xE4, 0x8B, 0x38, 0x0A, 0xAC, 0x72,
    0x21, 0xD4, 0xF8, 0x07,
};

static struct GbaHeader HEADER;
static bool WANT_TITLE;
static char TITLE[12];
static char GAME_CODE[4];
static char MAKER_CODE[2];
static bool HAVE_VERSION;
static uint8_t VERSION;
static bool HAVE_DEBUG;
static uint8_t DEBUG;
static bool HAVE_PADDING;
static size_t PADDING;
static const char *FILENAME;

void bail(const char *message, int code)
{
    fprintf(stderr, "%s\n", message);
    exit(code);
}

size_t pad(size_t n, size_t p)
{
    if (p == 0)
    {
        if (n > (SIZE_MAX / 2))
        {
            bail("cannot pad ROM", 4);
        }

        p = n - 1;
        p |= p >> 1;
        p |= p >> 2;
        p |= p >> 4;
        p |= p >> 8;
        p |= p >> 16;
        p += 1;

        return p;
    }
    else if (p == 1)
    {
        return n;
    }
    else
    {
        if (n > (SIZE_MAX - p - 1))
        {
            bail("cannot pad ROM", 4);
        }

        n += p - 1;

        return n - (n % p);
    }
}

FILE* rom_open(const char *s)
{
    FILE *f = fopen(s, "r+b");

    if (f == NULL)
    {
        bail("Failed to open ROM file", 1);
    }

    return f;
}

void rom_pad(FILE *f)
{
    fseek(f, 0, SEEK_END);
    size_t n = ftell(f);

    for (size_t m = pad(n, PADDING); n < m; n++)
    {
        if (fputc(0xFF, f) == EOF)
        {
            bail("failed to write ROM padding", 5);
        }
    }
}

void header_read(struct GbaHeader *h, FILE *f)
{
    fseek(f, 0, SEEK_SET);

    size_t n = fread(h, 1, sizeof(struct GbaHeader), f);

    if (n < sizeof(struct GbaHeader))
    {
        bail("Failed to read ROM header", 2);
    }
}

void header_write(const struct GbaHeader *h, FILE *f)
{
    fseek(f, 0, SEEK_SET);

    size_t n = fwrite(h, 1, sizeof(struct GbaHeader), f);

    if (n < sizeof(struct GbaHeader))
    {
        bail("Failed to write ROM header", 3);
    }
}

uint8_t header_checksum(const struct GbaHeader *h)
{
    const uint8_t *b = (const uint8_t *)h;

    uint8_t checksum = 0;

    for (size_t i = 0xA0; i < 0xBD; i++)
    {
        checksum -= b[i];
    }

    checksum -= 0x19;

    return checksum;
}

void header_fix(struct GbaHeader *h)
{
    memcpy(h->logo, NINTENDO_LOGO, sizeof(h->logo));

    if (TITLE[0])
    {
        memcpy(h->title, TITLE, sizeof(h->title));
    }

    if (GAME_CODE[0])
    {
        memcpy(h->game_code, GAME_CODE, sizeof(h->game_code));
    }

    if (MAKER_CODE[0])
    {
        memcpy(h->maker_code, MAKER_CODE, sizeof(h->maker_code));
    }

    h->hex96 = 0x96;
    h->unit_code = 0x00;

    if (HAVE_DEBUG)
    {
        h->logo[152] = 0xA5;
        h->device_type = DEBUG;
    }

    memset(h->reserved1, 0, sizeof(h->reserved1));

    if (HAVE_VERSION)
    {
        h->version = VERSION;
    }

    h->checksum = header_checksum(h);

    memset(h->reserved2, 0, sizeof(h->reserved2));
}

bool checked_strtoul(const char *s, unsigned long *v, unsigned long max)
{
    if (!s) { return false; }

    char *e;

    errno = 0;
    unsigned long a = strtoul(s, &e, 10);

    // Error if:
    // - No conversion
    // - Junk after number
    // - Result out of range
    // - Greater than max
    if (e == s || *e || errno == ERANGE || (max && a > max)) { return false; }

    *v = a;

    return true;
}

void options_get(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "--"))
        {
            if (!FILENAME)
            {
                FILENAME = argv[i + 1];
            }
            else if (argv[i + 1])
            {
                bail("too many filenames", 10);
            }
            break;
        }

        if (!strncmp(argv[i], "-t", 2))
        {
            if (TITLE[0] || WANT_TITLE)
            {
                bail("too many -t", 11);
            }

            if (argv[i][2])
            {
                if (strlen(argv[i] + 2) > 12)
                {
                    bail("bad title", 7);
                }

                strncpy(TITLE, argv[i] + 2, sizeof(TITLE));
            }
            else
            {
                WANT_TITLE = true;
            }

            continue;
        }

        if (!strncmp(argv[i], "-c", 2))
        {
            if (GAME_CODE[0])
            {
                bail("too many -c", 11);
            }

            const char *c = argv[i][2] ? argv[i] + 2 : argv[++i];

            if (!c || strlen(c) != 4)
            {
                bail("bad game code", 7);
            }

            strncpy(GAME_CODE, c, 4);

            continue;
        }

        if (!strncmp(argv[i], "-m", 2))
        {
            if (MAKER_CODE[0])
            {
                bail("too many -m", 11);
            }

            const char *c = argv[i][2] ? argv[i] + 2 : argv[++i];

            if (!c || strlen(c) != 2)
            {
                bail("bad maker code", 7);
            }

            strncpy(MAKER_CODE, c, 2);

            continue;
        }

        if (!strncmp(argv[i], "-r", 2))
        {
            if (HAVE_VERSION)
            {
                bail("too many -r", 11);
            }

            const char *c = argv[i][2] ? argv[i] + 2 : argv[++i];

            unsigned long v;

            if (!checked_strtoul(c, &v, 255))
            {
                bail("bad version", 7);
            }

            HAVE_VERSION = true;
            VERSION = (uint8_t)v;

            continue;
        }

        if (!strncmp(argv[i], "-d", 2))
        {
            if (HAVE_DEBUG)
            {
                bail("too many -d", 11);
            }

            unsigned long d;

            if (!argv[i][2])
            {
                bail("bad debug", 7);
            }

            if (!checked_strtoul(argv[i] + 2, &d, 1))
            {
                bail("bad debug", 7);
            }

            HAVE_DEBUG = true;
            DEBUG = (uint8_t)d;

            continue;
        }

        if (!strncmp(argv[i], "-p", 2))
        {
            if (HAVE_PADDING)
            {
                bail("too many -p", 11);
            }
            unsigned long p;

            if (!argv[i][2])
            {
                p = 0;
            }
            else if (!checked_strtoul(argv[i] + 2, &p, 0))
            {
                bail("bad padding", 7);
            }

            HAVE_PADDING = true;
            PADDING = p;

            continue;
        }

        if (argv[i][0] == '-')
        {
            bail("bad option", 9);
        }

        if (!FILENAME)
        {
            FILENAME = argv[i];
        }
        else
        {
            bail("too many filenames", 10);
        }
    }

    if (!FILENAME)
    {
        bail("missing filename", 6);
    }

    if (WANT_TITLE)
    {
        strncpy(TITLE, FILENAME, 12);
    }
}

void options_check(FILE *f)
{
    if (HAVE_PADDING)
    {
        size_t r = ftell(f);

        fseek(f, 0, SEEK_END);

        size_t n = ftell(f);

        fseek(f, r, SEEK_SET);

        pad(n, PADDING);
    }
}

void usage(const char *progname)
{
    printf("usage: %s [options] <rom file>\n\n", progname);

    puts("options:\n"
            "\t-t [title]   Game title, up to 12 characters\n"
            "\t-c <code>    Game code, 4 characters\n"
            "\t-m <code>    Maker code, 2 characters\n"
            "\t-r <version> Game version, number\n"
            "\t-p [N]       Pad ROM to next power of 2 or next multiple of N\n"
            "\t-d [0|1]     Enable debug handler");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        usage(argv[0]);
        exit(0);
    }

    options_get(argc, argv);

    FILE *f = rom_open(FILENAME);

    options_check(f);

    header_read(&HEADER, f);
    header_fix(&HEADER);
    header_write(&HEADER, f);

    if (HAVE_PADDING)
    {
        rom_pad(f);
    }

    fclose(f);

    return 0;
}
