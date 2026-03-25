#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define BASE 10

static int* matrix_create(int n)
{
    assert(n > 0 && "matrix_create: matrix size is invalid!");

    int total_len   = n * n;
    int* buffer     = malloc((size_t)total_len * sizeof(int));

    if (!buffer) {
        return NULL;
    }

    srand((unsigned)time(0));

    for (int i = 0; i < total_len; ++i) {
        buffer[i] = rand() % 10;
    }

    return buffer;
}

static void matrix_print(const int* buffer, int n)
{
    assert(buffer && n > 0 && "matrix_print: matrix is invalid!");

    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            printf("%3d%s", buffer[row * n + col], col == n - 1 ? "\n" : "");
        }
    }
}

static void matrix_transpose(int* buffer, int n)
{
    assert(buffer && n > 0 && "matrix_transpose: matrix is invalid!");

    for (int row = 0; row < n; ++row) {
        for (int col = row + 1; col < n; ++col) {

            int left_index  = row * n + col;
            int right_index = col * n + row;

            int tmp             = buffer[left_index];
            buffer[left_index]  = buffer[right_index];
            buffer[right_index] = tmp;
        }
    }
}

static void matrix_shift_cols(int* buffer, int n)
{
    assert(buffer && n > 0 && "matrix_shift_cols: matrix is invalid!");

    for (int row = 0; row < n; ++row) {

        for (int left_col = 0, right_col = n - 1; left_col < right_col; ++left_col, --right_col) {

            int left_index      = row * n + left_col;
            int right_index     = row * n + right_col;

            int tmp             = buffer[left_index];
            buffer[left_index]  = buffer[right_index];
            buffer[right_index] = tmp;
        }
    }
}

static void matrix_rotate_right(int* buffer, int n)
{
    assert(buffer && n > 0 && "matrix_print: matrix is invalid!");

    matrix_transpose(buffer, n);
    matrix_shift_cols(buffer, n);
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("usage: %s <N>\n", argv[0]);
        return 0;
    }

    char* error     = NULL;
    int n           = (int)strtol(argv[1], &error, BASE);

    if (*error) {
        fprintf(stderr, "%s: invalid character: '%c'\n", argv[0], *error);
        return 1;
    }

    if (n <= 0) {
        fprintf(stderr, "%s: invalid length\n", argv[0]);
        return 1;
    }

    int* matrix = matrix_create(n);
    if (!matrix) {
        fprintf(stderr, "%s: not enough memory\n", argv[0]);
        return 1;
    }

    matrix_print(matrix, n);

    putchar('\n');

    matrix_rotate_right(matrix, n);
    matrix_print(matrix, n);

    free(matrix);
    return 0;
}
