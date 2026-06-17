#include <stdio.h>
#include <string.h>

#define ABS(X) ((X) < 0 ? -(X) : (X))

static bool is_one_away(const char* p,
                        const char* q)
{
    if (!p || !q) {
        return false;
    }

    int p_len = (int)strlen(p);
    int q_len = (int)strlen(q);

    if (ABS(p_len - q_len) > 1) {
        return false;
    }

    const char* shorter = (p_len < q_len) ? p : q;
    const char* longer  = (shorter == p)  ? q : p;

    int diff = 0;

    while (*shorter && *longer) {

        if (*shorter == *longer) {
            ++shorter;
            ++longer;
        }
        else {
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
