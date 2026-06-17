#include <stdio.h>

#define EXT_ASCII_LEN 256

static bool is_unique(const char* s)
{
    if (!s) {
        return true;
    }

    bool bits[EXT_ASCII_LEN] = {};

    for (; *s; ++s) {

        if (bits[(int)*s]) {
            return false;
        }

        bits[(int)*s] = true;
    }

    return true;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <string>\n", argv[0]);
        return 0;
    }

    printf("%s: '%s' is %s\n", argv[0], argv[1], is_unique(argv[1]) ? "unique" : "NOT unique");

    return 0;
}
