#include "../inc/matrix.h"

struct matrix
{
    void **data;

    size_t row_count;
    size_t column_count;

    size_t el_size;
};

matrix_t *matrix_allocate(const size_t row_count, const size_t column_count,
const size_t el_size)
{
    LOG_INFO(">> (row_count == %zu, column_count == %zu, el_size == %zu)", 
    row_count, column_count, el_size);

    matrix_t *matrix = malloc(sizeof(matrix_t));

    if (NULL == matrix)
    {
        LOG_ERROR("<< Unable to allocate memory for matrix_t [%zu B]",
        sizeof(matrix));

        return NULL;
    }

    if (0 == row_count || 0 == column_count)
    {
        matrix->data = NULL;

        matrix->row_count = 0;
        matrix->column_count = 0;

        matrix->el_size = el_size;

        LOG_INFO("%s", "<< Zero size matrix");
        return matrix;
    }

    size_t matrix_array_size = row_count * sizeof(void *) +
    row_count * column_count * el_size;

    void **data = malloc(matrix_array_size);

    if (NULL == data)
    {
        free(matrix);

        LOG_ERROR("<< Unable to allocate memory for matrix data [%zu B]",
        matrix_array_size);

        return NULL;
    }


    void *p_arr = (void *) ((char *) data + row_count * sizeof(void *));

    for (size_t i = 0; i < row_count; ++i)
        data[i] = (char *) p_arr + i * column_count * el_size;

    matrix->data = data;

    matrix->row_count = row_count;
    matrix->column_count = column_count;

    matrix->el_size = el_size;

    LOG_INFO("%s", "<< Default return");
    return matrix;
}

void matrix_free(matrix_t *matrix)
{
    if (NULL == matrix)
    {
        LOG_WARNING("%s", "<< NULL == matrix");
        return;
    }
    
    LOG_IF_ERROR(NULL == matrix->data, "%s", "matrix.data == NULL");

    free(matrix->data);

    free(matrix);

    matrix = NULL;
}

void *matrix_get_ptr_to(const matrix_t *matrix, const size_t row_i,
const size_t column_i)
{
    assert(row_i < matrix->row_count);
    assert(column_i < matrix->column_count);

    return (void *) ((char *) matrix->data[row_i] + column_i * matrix->el_size);
}

double matrix_get_double_at(const matrix_t *matrix, const size_t row_i,
const size_t column_i)
{
    assert(sizeof(double) == matrix->el_size);

    return *((double *) matrix_get_ptr_to(matrix, row_i, column_i));
}

void matrix_set_double_at(const matrix_t *const matrix, const size_t row_i,
const size_t column_i, double const value)
{
    assert(sizeof(double) == matrix->el_size);

    *((double *) matrix_get_ptr_to(matrix, row_i, column_i)) = value;
}

size_t matrix_get_row_count(matrix_t *matrix)
{
    return matrix->row_count;
}

size_t matrix_get_column_count(matrix_t *matrix)
{
    return matrix->column_count;
}

size_t matrix_get_el_size(matrix_t *matrix)
{
    return matrix->el_size;
}

void matrix_swap_rows(matrix_t *matrix, size_t f_row_i, size_t s_row_i)
{
    LOG_DEBUG(">> f_row_i = %zu; s_row_i = %zu", f_row_i, s_row_i);
    assert(f_row_i < matrix->row_count);
    assert(s_row_i < matrix->row_count);

    void *bucket = matrix->data[f_row_i];
    matrix->data[f_row_i] = matrix->data[s_row_i];
    matrix->data[s_row_i] = bucket;
}
