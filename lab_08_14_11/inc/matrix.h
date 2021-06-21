#ifndef __MATRIX_H__

#define __MATRIX_H__

#include <stdlib.h>
#include <assert.h>

#include "macrologger.h"

struct matrix;

typedef struct matrix matrix_t;

/**
 * @brief Create dynamic matrix
 *
 * @return Matrix if success;
 * NULL if unable allocate memory for matrix;
 */
matrix_t *matrix_allocate(const size_t row_count, const size_t column_count,
const size_t el_size);

/**
 * @brief Free dymanic matrix
 *
 * If NULL == matrix || NULL == matrix.data -> no error expected
 */
void matrix_free(matrix_t *matrix);

/**
 * @brief Calculate ptr to element of matrix by index
 *
 * @return Pointer to matrix element by index i
 */
void *matrix_get_ptr_to(const matrix_t *matrix, const size_t row_i,
const size_t column_i);

/**
 * @brief Return double value by row, column index in dynamic matrix
 *
 * @return Double value by row, column index in dynamic matrix
 */
double matrix_get_double_at(const matrix_t *matrix, const size_t row_i,
const size_t column_i);

/**
 * @brief Set double value by row, column index in dynamic matrix
 */
void matrix_set_double_at(const matrix_t *const matrix, const size_t row_i,
const size_t column_i, double const value);

/**
 * @return Row count of matrix
 */
size_t matrix_get_row_count(matrix_t *matrix);

/**
 * @return Column count of matrix
 */
size_t matrix_get_column_count(matrix_t *matrix);

/**
 * @return Return el size
 */
size_t matrix_get_el_size(matrix_t *matrix);

void matrix_swap_rows(matrix_t *matrix, size_t f_row_i, size_t s_row_i);

#endif // __MATRIX_H__
