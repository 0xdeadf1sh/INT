#include <stdio.h>

static bool has_sufficient_space(const char* s)
{
    if (!s) {
        return false;
    }

    int spaces  = 0;
    int total   = 0;
    int len     = 0;

    for (; s[len]; ++len) {
        if (s[len] == ' ') {
            ++spaces;
        }
        else {
            total += 1 + spaces * 3;
            spaces = 0;
        }
    }

    return total && total <= len;
}

static void urlify(char* s)
{
    if (!s) {
        return;
    }

    int len = 0;
    for (; s[len]; ++len)
        ;

    int last_nonspace_ind = len - 1;
    for (int i = len - 1; i >= 0; --i) {
        if (s[i] != ' ') {
            last_nonspace_ind = i;
            break;
        }
    }

    int write_ind = len;
    for (int read_ind = last_nonspace_ind; read_ind >= 0; --read_ind) {
        if (s[read_ind] == ' ') {
            s[--write_ind] = '%';
            s[--write_ind] = '0';
            s[--write_ind] = '2';
        }
        else {
            s[--write_ind] = s[read_ind];
        }
    }

    for (int i = 0; i < len - write_ind; ++i) {
        s[i] = s[i + write_ind];
    }

    s[len - write_ind] = '\0';
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("usage: %s <string>\n", argv[0]);
        return 0;
    }

    if (!has_sufficient_space(argv[1])) {
        printf("%s: '%s' doesn't have enough sufficient space!\n", argv[0], argv[1]);
        return 0;
    }

    urlify(argv[1]);

    printf("urlified: '%s'\n", argv[1]);

    return 0;
}
