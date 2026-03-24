#include <stdio.h>

#define EXT_ASCII_LEN 256

static bool is_permutation(const char* restrict p,
                           const char* restrict q)
{
    if (!p || !q) {
        return false;
    }

    int counts[EXT_ASCII_LEN] = {};

    for (; *p; ++p) {
        ++counts[(int)*p];
    }

    for (; *q; ++q) {
        --counts[(int)*q];
    }

    for (int i = 0; i < EXT_ASCII_LEN; ++i) {
        if (counts[i]) {
            return false;
        }
    }

    return true;
}

int main(int argc, char** argv)
{
    if (argc < 3) {
        printf("usage: %s <string> <string>\n", argv[0]);
        return 0;
    }

    printf("%s: '%s' is %s of '%s'\n", argv[0],
                                       argv[1],
                                       is_permutation(argv[1], argv[2]) ? "permutation" : "NOT permutation",
                                       argv[2]);

    return 0;
}
