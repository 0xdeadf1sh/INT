#include <stdio.h>
#include <ctype.h>

#define EXT_ASCII_LEN 256

static bool is_palindrome_of_permutation(const char* s)
{
    if (!s) {
        return false;
    }

    bool state[EXT_ASCII_LEN] = {};

    for (; *s; ++s) {
        if (isalnum(*s)) {
            int c = tolower(*s);
            state[c] = !state[c];
        }
    }

    int odd_count = 0;

    for (int i = 0; i < EXT_ASCII_LEN; ++i) {
        if (state[i]) {
            ++odd_count;
        }
    }

    return odd_count <= 1;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("usage: %s <string>\n", argv[0]);
        return 0;
    }

    printf("%s: '%s' is%s a permutation of palindrome\n", argv[0],
                                                          argv[1],
                                                          is_palindrome_of_permutation(argv[1]) ? "" : " NOT");

    return 0;
}
