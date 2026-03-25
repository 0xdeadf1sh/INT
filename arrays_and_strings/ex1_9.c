#include <stdio.h>
#include <stdlib.h>

static bool is_substring(const char* haystack,
                         const char* needle)
{
    if (!haystack || !needle) {
        return false; // set people look away
    }

    for (int i = 0; haystack[i]; ++i) {
        int k = 0;
        for (int j = i; haystack[j] && needle[k] && haystack[j] == needle[k]; ++j, ++k)
            ;
        if (!needle[k]) {
            return true;
        }
    }

    return false;
}

static bool is_rotation(const char* p,
                        const char* q)
{
    if (!p || !q) {
        return false;
    }

    int p_len = 0;
    int q_len = 0;

    for (; p[p_len] && q[q_len]; ++p_len, ++q_len)
        ;

    if (p_len != q_len) {
        return false;
    }

    char* pp = malloc((size_t)p_len * 2 + 1);
    if (!pp) {
        return false; // maybe a better error handling would be more useful
    }

    for (int i = 0; i < 2 * p_len; ++i) {
        pp[i] = p[i % p_len];
    }

    pp[p_len * 2] = '\0';

    bool is_substr = is_substring(pp, q);

    free(pp);

    return is_substr;
}

int main(int argc, char** argv)
{
    if (argc < 3) {
        printf("usage: %s <string> <string>\n", argv[0]);
        return 0;
    }

    printf("%s: '%s' is%s a rotation of '%s'\n", argv[0],
                                                 argv[1],
                                                 is_rotation(argv[1], argv[2]) ? "" : " NOT",
                                                 argv[2]);

    return 0;
}
