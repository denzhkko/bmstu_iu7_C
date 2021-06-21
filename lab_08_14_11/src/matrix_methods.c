#include "../inc/matrix_methods.h"

matrix_t *fptr_to_double_matrix(FILE *source)
{
    int rc;
    size_t row_count, col_count;

    rc = scanf_size_t(source, &row_count);

    if (1 != rc)
    {
        LOG_ERROR("Row count read failed; scanf_size_t = %d", rc);
        return NULL;
    }

    rc = scanf_size_t(source, &col_count);

    if (1 != rc)
    {
        LOG_ERROR("Col count read failed; scanf_size_t = %d", rc);
        return NULL;
    }

    LOG_INFO("row_count = %zu; col_count = %zu", row_count, col_count);

    if (0 == row_count || 0 == col_count)
    {
        LOG_WARNING("%s", "0 matrix size");

        row_count = 0;
        col_count = 0;
    }

    matrix_t *matrix = matrix_allocate(row_count, col_count, sizeof(double));

    if (NULL == matrix)
    {
        LOG_ERROR("%s", "Matrix allocation failed");
        return NULL;
    }

    double matrix_el;
    for (size_t i = 0; i < row_count; ++i)
        for (size_t j = 0; j < col_count; ++j)
        {
            rc = fscanf(source, "%lf", &matrix_el);

            if (1 != rc)
            {
                LOG_ERROR("Incorrect matrix data [%zu][%zu]", i, j);

                matrix_free(matrix);
                return NULL;
            }

            matrix_set_double_at(matrix, i, j, matrix_el);
        }

    if (1 == fscanf(source, "%lf", &matrix_el))
    {
        LOG_ERROR("%s", "Extra matrix elems");

        matrix_free(matrix);
        return NULL;
    }

    return matrix;
}

matrix_t *file_to_double_matrix(char *filename)
{
    LOG_INFO(">> filename = %s", filename);

    matrix_t *matrix = NULL;

    FILE *f = fopen(filename, "r");

    if (NULL == f)
    {
        LOG_ERROR("%s", "File cannot be opened");
        return NULL;
    }

    matrix = fptr_to_double_matrix(f);

    if (NULL == matrix)
    {
        LOG_ERROR("%s", "Reading matrix failed");
    }

    if (EOF == fclose(f))
    {
        LOG_ERROR("fclose failed: %s", strerror(errno));
        matrix_free(matrix);
    }

    return matrix;
}

void print_double_matrix(FILE *source, matrix_t *matrix)
{
    size_t row_count = matrix_get_row_count(matrix);
    size_t col_count = matrix_get_column_count(matrix);

    fprintf(source, "%zu %zu\n", row_count, col_count);

    for (size_t i = 0; i < row_count; ++i)
    {
        for (size_t j = 0; j < col_count; ++j)
            fprintf(source, "%.5lf ", matrix_get_double_at(matrix, i, j));
        fprintf(source, "\n");
    }
}

int double_matrix_to_file(matrix_t *matrix, char *filename)
{
    assert(NULL != matrix);
    assert(NULL != filename);

    int grc = OKAY;

    FILE *f = fopen(filename, "w");

    if (NULL != f)
    {
        print_double_matrix(f, matrix);

        if (EOF == fclose(f))
        {
            LOG_ERROR("Fclose by %s failed", filename);
            grc = FCLOSE_FAILED;
        }
    }
    else
    {
        LOG_ERROR("File %s cannot be opened", filename);
        grc = FILE_CANNOT_BE_OPENED;
    }

    return grc;
}

int invert_double_matrix(matrix_t **matrix_ptr)
{
    assert(NULL != matrix_ptr);
    matrix_t *matrix = *matrix_ptr;
    assert(NULL != matrix);

    size_t m_row_count = matrix_get_row_count(matrix);
    size_t m_col_count = matrix_get_column_count(matrix);

    assert(m_row_count == m_col_count);
    assert(m_row_count > 0);
    assert(m_col_count > 0);

    matrix_t *invert_matrix = matrix_allocate(m_row_count,
    m_col_count, sizeof(double));

    if (NULL == invert_matrix)
    {
        LOG_ERROR("%s", "<< Unable to allocate invert_matrix");
        return ALLOCATION_FAILED;
    }

    for (size_t i = 0; i < m_row_count; ++i)
    {
        for (size_t j = 0; j < m_col_count; ++j)
            matrix_set_double_at(invert_matrix, i, j, 0.0);
        matrix_set_double_at(invert_matrix, i, i, 1.0);
    }

    for (size_t col_i = 0; col_i < m_col_count; ++col_i)
    {
        if (IS_DOUBLE_EQ(matrix_get_double_at(matrix, col_i, col_i), 0.0))
        {
            bool is_rows_swapped = false;
            for (size_t i = col_i + 1; i < m_row_count; ++i)
            {
                double under_v = matrix_get_double_at(matrix, i, col_i);

                if (!IS_DOUBLE_EQ(under_v, 0.0))
                {
                    matrix_swap_rows(matrix, col_i, i);
                    matrix_swap_rows(invert_matrix, col_i, i);
                    is_rows_swapped = true;

                    LOG_INFO("Rows %zu and %zu swapped", col_i, i);

                    break;
                }
            }

            if (!is_rows_swapped)
            {
                LOG_ERROR("<< Unable to find nonzero values under [%zu][%zu]",
                col_i, col_i);

                matrix_free(invert_matrix);

                return ZERO_DETERMINANT;
            }
        }

        for (size_t row_i = 0; row_i < m_row_count; ++row_i)
        {
            if (row_i == col_i)
                continue;

            double coefficient = (matrix_get_double_at(matrix, row_i, col_i) /
                    matrix_get_double_at(matrix, col_i, col_i));

            bool is_only_zero = true;
            for (size_t j = 0; j < m_col_count; ++j)
            {
                double row_value, pre_value;

                row_value = matrix_get_double_at(matrix, col_i, j);
                pre_value = matrix_get_double_at(matrix, row_i, j);
                matrix_set_double_at(matrix, row_i, j,
                        pre_value - coefficient * row_value);

                row_value = matrix_get_double_at(invert_matrix, col_i, j);
                pre_value = matrix_get_double_at(invert_matrix, row_i, j);
                matrix_set_double_at(invert_matrix, row_i, j,
                        pre_value - coefficient * row_value);

                double value = matrix_get_double_at(matrix, row_i, j);

                if (fabs(value) > DOUBLE_TOL)
                    is_only_zero = false;
            }

            if (is_only_zero)
            {
                matrix_free(invert_matrix);
                LOG_ERROR("<< Zero elem row found; row = %zu", row_i);
                return ZERO_DETERMINANT;
            }
        }
    }

    for (size_t i = 0; i < m_row_count; ++i)
    {
        double diagonal_el = matrix_get_double_at(matrix, i, i);

        for (size_t j = 0; j < m_col_count; ++j)
        {
            double prev_value = matrix_get_double_at(invert_matrix, i, j);
            matrix_set_double_at(invert_matrix, i, j,
            prev_value / diagonal_el);
        }

        double prev_value = matrix_get_double_at(matrix, i, i);
        matrix_set_double_at(matrix, i, i, prev_value / diagonal_el);
    }

    LOG_INFO("%s", "<< Success");
    matrix_free(matrix);
    *matrix_ptr = invert_matrix;
    return OKAY;
}

matrix_t *get_double_matrix_sum(matrix_t *f_matrix, matrix_t *s_matrix)
{
    assert(NULL != f_matrix);
    assert(NULL != s_matrix);

    assert(matrix_get_el_size(f_matrix) == sizeof(double));
    assert(matrix_get_el_size(s_matrix) == sizeof(double));

    size_t fm_row_count = matrix_get_row_count(f_matrix);
    size_t fm_col_count = matrix_get_column_count(f_matrix);

    size_t sm_row_count = matrix_get_row_count(s_matrix);
    size_t sm_col_count = matrix_get_column_count(s_matrix);

    assert(fm_row_count == sm_row_count);
    assert(fm_col_count == sm_col_count);

    size_t m_row_count = fm_row_count;
    size_t m_col_count = fm_col_count;

    assert(m_row_count > 0);
    assert(m_col_count > 0);

    matrix_t *matrix_sum = matrix_allocate(m_row_count,
    m_col_count, sizeof(double));

    if (NULL == matrix_sum)
    {
        LOG_ERROR("%s", "<< Unable to allocate sum_matrix");
        return NULL;
    }

    for (size_t i = 0; i < m_row_count; ++i)
        for (size_t j = 0; j < m_col_count; ++j)
        {
            double fm_el = matrix_get_double_at(f_matrix, i, j);
            double sm_el = matrix_get_double_at(s_matrix, i, j);

            matrix_set_double_at(matrix_sum, i, j, fm_el + sm_el);
        }

    return matrix_sum;
}

matrix_t *get_double_matrix_product(matrix_t *f_matrix, matrix_t *s_matrix)
{
    assert(NULL != f_matrix);
    assert(NULL != s_matrix);

    assert(matrix_get_el_size(f_matrix) == sizeof(double));
    assert(matrix_get_el_size(s_matrix) == sizeof(double));

    size_t fm_row_count = matrix_get_row_count(f_matrix);
    size_t fm_col_count = matrix_get_column_count(f_matrix);

    size_t sm_row_count = matrix_get_row_count(s_matrix);
    size_t sm_col_count = matrix_get_column_count(s_matrix);

    assert(fm_row_count > 0);
    assert(fm_col_count > 0);
    assert(sm_row_count > 0);
    assert(sm_col_count > 0);

    assert(fm_col_count == sm_row_count);

    size_t p_row_count = fm_row_count;
    size_t p_col_count = sm_col_count;

    matrix_t *product = matrix_allocate(p_row_count, p_col_count,
    sizeof(double));

    if (NULL == product)
    {
        LOG_ERROR("%s", "<< Unable to allocate product matrix");

        return NULL;
    }

    for (size_t row_i = 0; row_i < p_row_count; ++row_i)
        for (size_t col_i = 0; col_i < p_col_count; ++col_i)
        {
            matrix_set_double_at(product, row_i, col_i, 0.0);

            for (size_t i = 0; i < fm_col_count; ++i)
            {
                double fm_el = matrix_get_double_at(f_matrix, row_i, i);
                double sm_el = matrix_get_double_at(s_matrix, i, col_i);
                double p_el = matrix_get_double_at(product, row_i, col_i);

                matrix_set_double_at(product, row_i, col_i,
                p_el + fm_el * sm_el);
            }
        }

    return product;
}
