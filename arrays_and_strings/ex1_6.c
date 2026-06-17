#include <stdio.h>

static int count_digits(int n)
{
    int k = n / 10;
    if (k) {
        return 1 + count_digits(k);
    }

    return 1;
}

static bool can_be_compressed(const char* s)
{
    if (!s) {
        return false;
    }

    int s_len = 0;
    for (; s[s_len]; ++s_len)
        ;

    int last_letter     = *s;
    int last_letter_cnt = 0;
    int compressed_len  = 0;

    for (; *s; ++s) {
        if (*s == last_letter) {
            ++last_letter_cnt;
        }
        else {
            ++compressed_len;
            if (last_letter_cnt > 1) {
                compressed_len += count_digits(last_letter_cnt);
            }
            last_letter_cnt = 1;
            last_letter = *s;
        }
    }

    if (last_letter_cnt) {
        ++compressed_len;
        if (last_letter_cnt > 1) {
            compressed_len += count_digits(last_letter_cnt);
        }
    }

    return compressed_len < s_len;
}

static int write_digits(char* buffer, int write_index, int k)
{
    int m = k / 10;
    if (m) {
        write_index = write_digits(buffer, write_index, m);
    }

    buffer[write_index++] = (char)(k % 10 + '0');

    return write_index;
}

static void compress(char* s)
{
    if (!s) {
        return;
    }

    int read_ind        = 0;
    int write_ind       = 0;
    int last_letter     = *s;
    int last_letter_cnt = 0;

    for (; s[read_ind]; ++read_ind) {
        if (s[read_ind] == last_letter) {
            ++last_letter_cnt;
        }
        else {
            s[write_ind++] = (char)last_letter;
            if (last_letter_cnt > 1) {
                write_ind = write_digits(s, write_ind, last_letter_cnt);
            }
            last_letter = s[read_ind];
            last_letter_cnt = 1;
        }
    }

    if (last_letter_cnt) {
        s[write_ind++] = (char)last_letter;
        if (last_letter_cnt > 1) {
            write_ind = write_digits(s, write_ind, last_letter_cnt);
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

    if (!can_be_compressed(argv[1])) {
        printf("'%s'\n", argv[1]);
        return 0;
    }

    compress(argv[1]);
    printf("'%s'\n", argv[1]);

    return 0;
}
