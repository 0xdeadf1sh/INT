#include <stdio.h>
#include <ctype.h>

static bool has_sufficient_space(const char* s)
{
    if (!s) {
        return false;
    }

    int spaces      = 0;
    int urlified    = 0;
    int len         = 0;

    for (; s[len]; ++len) {
        if (s[len] == ' ') {
            ++spaces;
        }
        else {
            urlified += 1 + spaces * 3;
            spaces = 0;
        }
    }

    return urlified && urlified <= len;
}

static void shift_right(char* s, int k, int len)
{
    for (int i = len - 1, j = i - k; j >= 0; --i, --j) {
        s[i] = s[j];
    }
}

static void urlify(char* s)
{
    if (!s) {
        return;
    }

    int len = 0;
    int trailing_blank_cnt = 0;

    for (; s[len]; ++len) {
        if (isspace(s[len])) {
            ++trailing_blank_cnt;
        }
        else {
            trailing_blank_cnt = 0;
        }
    }

    shift_right(s, trailing_blank_cnt, len);

    int read_ind = trailing_blank_cnt;
    int write_ind = 0;

    for (; read_ind < len; ++read_ind) {
        if (isspace(s[read_ind])) {
            s[write_ind++] = '%';
            s[write_ind++] = '2';
            s[write_ind++] = '0';
        }
        else {
            s[write_ind++] = s[read_ind];
        }
    }

    s[write_ind] = '\0';
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
