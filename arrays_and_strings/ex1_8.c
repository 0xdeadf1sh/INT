#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define BASE 10

static int* matrix_create(int rows, int cols)
{
    assert(rows > 0 && cols > 0 && "matrix_create: invalid rows/cols");

    int total_len   = rows * cols;
    int* buffer     = malloc(sizeof(int) * (size_t)total_len);

    if (!buffer) {
        return NULL;
    }

    srand((unsigned)time(0));

    for (int i = 0; i < total_len; ++i) {
        buffer[i] = rand() % 10;
    }

    return buffer;
}

static void matrix_print(const int* buffer, int rows, int cols)
{
    assert(buffer && rows > 0 && cols > 0 && "matrix_print: matrix is invalid");

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            printf("%3d%s", buffer[row * cols + col], col == cols - 1 ? "\n" : "");
        }
    }
}

static void matrix_zero(int* buffer, int rows, int cols)
{
    assert(buffer && rows > 0 && cols > 0 && "matrix_zero: matrix is invalid");

    bool first_row_has_zero = false;
    for (int col = 0; col < cols; ++col) {
        if (!buffer[col]) {
            first_row_has_zero = true;
            break;
        }
    }

    bool first_col_has_zero = false;
    for (int row = 0; row < rows; ++row) {
        if (!buffer[row * cols]) {
            first_col_has_zero = true;
            break;
        }
    }

    for (int row = 1; row < rows; ++row) {
        for (int col = 1; col < cols; ++col) {
            if (!buffer[row * cols + col]) {
                buffer[col] = buffer[row * cols] = 0;
            }
        }
    }

    for (int col = 1; col < cols; ++col) {
        if (!buffer[col]) {
            for (int row = 1; row < rows; ++row) {
                buffer[row * cols + col] = 0;
            }
        }
    }

    for (int row = 1; row < rows; ++row) {
        if (!buffer[row * cols]) {
            for (int col = 1; col < cols; ++col) {
                buffer[row * cols + col] = 0;
            }
        }
    }

    if (first_col_has_zero) {
        for (int col = 0; col < cols; ++col) {
            if (!buffer[col]) {
                for (int row = 0; row < rows; ++row) {
                    buffer[row * cols + col] = 0;
                }
            }
        }
    }

    if (first_row_has_zero) {
        for (int row = 0; row < rows; ++row) {
            if (!buffer[row * cols]) {
                for (int col = 0; col < cols; ++col) {
                    buffer[row * cols + col] = 0;
                }
            }
        }
    }
}

int main(int argc, char** argv)
{
    if (argc < 3) {
        printf("usage: %s <rows> <cols>\n", argv[0]);
        return 0;
    }

    char* rows_error = NULL;
    int rows = (int)strtol(argv[1], &rows_error, BASE);

    if (*rows_error) {
        fprintf(stderr, "%s: invalid character: '%c'\n", argv[0], *rows_error);
        return 1;
    }

    if (rows <= 0) {
        fprintf(stderr, "%s: invalid row count\n", argv[0]);
        return 1;
    }

    char* cols_error = NULL;
    int cols = (int)strtol(argv[2], &cols_error, BASE);

    if (*cols_error) {
        fprintf(stderr, "%s: invalid character: '%c'\n", argv[0], *cols_error);
        return 1;
    }

    if (cols <= 0) {
        fprintf(stderr, "%s: invalid col count\n", argv[0]);
        return 1;
    }

    int* matrix = matrix_create(rows, cols);
    if (!matrix) {
        fprintf(stderr, "%s: not enough memory\n", argv[0]);
        return 1;
    }

    matrix_print(matrix, rows, cols);

    putchar('\n');

    matrix_zero(matrix, rows, cols);
    matrix_print(matrix, rows, cols);

    free(matrix);
    return 0;
}
