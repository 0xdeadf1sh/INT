#include <stdio.h>

#define ABS(X) ((X) < 0 ? -(X) : (X))

static bool is_one_away(const char* p,
                        const char* q)
{
    if (!p || !q) {
        return false;
    }

    int p_len = 0;
    for (; p[p_len]; ++p_len)
        ;

    int q_len = 0;
    for (; q[q_len]; ++q_len)
        ;

    if (ABS(p_len - q_len) > 1) {
        return false;
    }

    const char* shorter = (p_len < q_len) ? p : q;
    const char* longer  = (shorter == q)  ? p : q;

    int diff = 0;

    while (*shorter && *longer) {

        if (*shorter != *longer) {

            ++diff;

            if (diff > 1) {
                return false;
            }

            if (p_len == q_len) {
                ++shorter;
                ++longer;
            }
            else {
                ++longer;
            }
        }
        else {
            ++shorter;
            ++longer;
        }
    }

    for (; *longer; ++longer) {
        ++diff;
    }

    return diff <= 1;
}

int main(int argc, char** argv)
{
    if (argc < 3) {
        printf("usage: %s <string> <string>\n", argv[0]);
        return 0;
    }

    printf("is_one_away('%s', '%s'): %d\n", argv[1], argv[2], is_one_away(argv[1], argv[2]));

    return 0;
}
