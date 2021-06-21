#ifndef __MATRIX_METHOD_H__

#define __MATRIX_METHOD_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "macrologger.h"

typedef struct
{
    int **data;
    size_t row_count;
    size_t column_count;
} matrix_t;

#define OKAY                            0
#define FILE_NOT_FOUND                  1
#define ALLOCATION_FAILED               2
#define INCORRECT_FILE                  3
#define UNABLE_REWRITE_FILE             4
#define REALLOCATION_FAILED             5

#define COUNT_PLUS(i, j) \
if (i >= 0 && i < matrix->row_count && j >= 0 && j < matrix->column_count) \
if (-1 == matrix->data[i][j]) \
++count;

int file_to_matrix(char *filename, matrix_t *matrix);

void matrix_free(matrix_t *matrix);

void saper(matrix_t *matrix);

int matrix_to_file(char *filename, matrix_t *matrix);

int delete_rows(matrix_t *matrix);

void matrix_print(FILE *sourse, matrix_t *matrix);

#endif // __MATRIX_METHOD_H__
