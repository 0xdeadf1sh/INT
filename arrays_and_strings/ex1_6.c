#include <stdio.h>
#include <stdlib.h>

static int count_digits(int n)
{
    int cnt = 0;

    do {
        ++cnt;
    }
    while (n /= 10);

    return cnt;
}

static bool can_be_compressed(const char* s, int* new_len)
{
    if (!s) {
        return false;
    }

    int s_len = 0;
    for (; s[s_len]; ++s_len)
        ;

    int last_letter     = s[0];
    int last_letter_cnt = 0;
    int compressed_len  = 0;

    for (int read_ind = 0; s[read_ind]; ++read_ind) {
        if (s[read_ind] == last_letter) {
            ++last_letter_cnt;
        }
        else {
            compressed_len += 1 + count_digits(last_letter_cnt);
            last_letter = s[read_ind];
            last_letter_cnt = 1;
        }
    }

    if (last_letter_cnt) {
        compressed_len += 1 + count_digits(last_letter_cnt);
    }

    *new_len = compressed_len;
    return compressed_len < s_len;
}

static int write_digits(char* buffer, int write_index, int k)
{
    if (k / 10) {
        write_index = write_digits(buffer, write_index, k / 10);
    }

    buffer[write_index++] = (char)(k % 10 + '0');

    return write_index;
}

static char* compress(char* s)
{
    if (!s) {
        return s;
    }

    int compressed_len = 0;
    if (!can_be_compressed(s, &compressed_len)) {
        return s;
    }

    char* buffer = malloc((size_t)compressed_len + 1);
    if (!buffer) {
        return s;
    }

    int read_ind        = 0;
    int write_ind       = 0;
    int last_letter     = s[0];
    int last_letter_cnt = 0;

    for (; s[read_ind]; ++read_ind) {
        if (s[read_ind] == last_letter) {
            ++last_letter_cnt;
        }
        else {
            buffer[write_ind++] = (char)last_letter;
            write_ind = write_digits(buffer, write_ind, last_letter_cnt);
            last_letter = s[read_ind];
            last_letter_cnt = 1;
        }
    }

    if (last_letter_cnt) {
        buffer[write_ind++] = (char)last_letter;
        write_ind = write_digits(buffer, write_ind, last_letter_cnt);
    }

    buffer[write_ind] = '\0';

    return buffer;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("usage: %s <string>\n", argv[0]);
        return 0;
    }

    char* buffer = compress(argv[1]);
    printf("'%s'\n", buffer);

    if (buffer != argv[1]) {
        free(buffer);
    }

    return 0;
}
