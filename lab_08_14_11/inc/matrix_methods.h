#ifndef __MATRIX_METHODS__

#define __MATRIX_METHODS__

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <errno.h>

#include "matrix.h"

#include "strio.h"
#include "double.h"

matrix_t *file_to_double_matrix(char *filename);

void print_double_matrix(FILE *source, matrix_t *matrix);

#define OKAY                            0
#define FILE_CANNOT_BE_OPENED           129
#define FCLOSE_FAILED                   130
int double_matrix_to_file(matrix_t *matrix, char *filename);

#define OKAY                            0
#define ALLOCATION_FAILED               1
#define ZERO_DETERMINANT                2
int invert_double_matrix(matrix_t **matrix_ptr);

matrix_t *get_double_matrix_sum(matrix_t *f_matrix, matrix_t *s_matrix);

matrix_t *get_double_matrix_product(matrix_t *f_matrix, matrix_t *s_matrix);

#endif // __MATRIX_METHODS__
