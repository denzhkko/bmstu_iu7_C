#include "../inc/menu.h"

bool is_matrixes_suit_for_sum(matrix_t *first_matrix, matrix_t *second_matrix)
{
    if (NULL == first_matrix || NULL == second_matrix)
    {
        LOG_ERROR("<< Null ptr in args: fm = %p; sm = %p",
        (void *) first_matrix, (void *) second_matrix);

        return false;
    }

    size_t fm_row_count = matrix_get_row_count(first_matrix);
    size_t fm_col_count = matrix_get_column_count(first_matrix);
    size_t sm_row_count = matrix_get_row_count(second_matrix);
    size_t sm_col_count = matrix_get_column_count(second_matrix);

    if (fm_row_count != sm_row_count)
    {
        LOG_ERROR("<< Row count source matrices is deff: %zu vs %zu",
        fm_row_count, sm_row_count);

        return false;
    }
    
    if (fm_col_count != sm_col_count)
    {
        LOG_ERROR("<< Col count source matrices is deff: %zu vs %zu",
        fm_col_count, sm_col_count);

        return false;
    }

    if (!(fm_row_count && fm_col_count && sm_row_count && sm_col_count))
    {
        LOG_ERROR("<< Some matrix size if zero: %zux%zu %zux%zu",
        fm_row_count, fm_col_count, sm_row_count, sm_col_count);

        return false;
    }

    return true;
}

int two_file_to_matrices(char *fm_filename, char *sm_filename,
matrix_t **first_matrix, matrix_t **second_matrix)
{
    *first_matrix = file_to_double_matrix(fm_filename);

    if (*first_matrix)
    {
        *second_matrix = file_to_double_matrix(sm_filename);

        if (*second_matrix)
        {
            return OKAY;
        }
        else
        {
            LOG_ERROR("%s", "<< Unable to allocate second matrix");
            matrix_free(*second_matrix);
        }

        matrix_free(*first_matrix);
    }
    else
    {
        LOG_ERROR("%s", "<< Unable to allocate first matrix");
    }

    return ALLOCATION_FAILED;
}

int menu_case_sum(char *fm_filename, char *sm_filename, char *out_filename)
{
    int grc = OKAY;

    matrix_t *first_matrix, *second_matrix;

    if (OKAY != two_file_to_matrices(fm_filename, sm_filename,
    &first_matrix, &second_matrix))
    {
        LOG_ERROR("%s", "<< Unable to allocate matrices");
        return ALLOCATION_FAULT;
    }

    if (is_matrixes_suit_for_sum(first_matrix, second_matrix))
    {
        matrix_t *sum_matrix = get_double_matrix_sum(first_matrix,
        second_matrix);

        if (sum_matrix)
        {
            if (OKAY == double_matrix_to_file(sum_matrix, out_filename))
            {
                LOG_INFO("%s", "Menu case sum ended success");
            }
            else
            {
                LOG_ERROR("Printing to %s failed", out_filename);
                grc = PRINT_FAILED;
            }

            matrix_free(sum_matrix);
        }
        else
        {
            LOG_ERROR("%s", "<< Unable to allocate sum matrix");
            grc = ALLOCATION_FAULT;
        }
    }
    else
    {
        LOG_ERROR("%s", "<< Matrices is not suite for sum");
        grc = MATRIXES_ISNOT_SUIT;
    }
    
    matrix_free(second_matrix);
    matrix_free(first_matrix);

    return grc;
}

bool is_matrixes_suit_for_multipe(matrix_t *first_matrix,
matrix_t *second_matrix)
{
    if (NULL == first_matrix || NULL == second_matrix)
    {
        LOG_ERROR("<< Null ptr in args: fm = %p; sm = %p",
        (void *) first_matrix, (void *) second_matrix);

        return false;
    }

    size_t fm_row_count = matrix_get_row_count(first_matrix);
    size_t fm_col_count = matrix_get_column_count(first_matrix);
    size_t sm_row_count = matrix_get_row_count(second_matrix);
    size_t sm_col_count = matrix_get_column_count(second_matrix);

    if (fm_col_count != sm_row_count)
    {
        LOG_ERROR("fm_col_count != sm_row_count; %zu vs %zu",
        fm_col_count, sm_row_count);

        return false;
    }
    
    if (!(fm_row_count && fm_col_count && sm_row_count && sm_col_count))
    {
        LOG_ERROR("<< Some matrix size if zero: %zux%zu %zux%zu",
        fm_row_count, fm_col_count, sm_row_count, sm_col_count);

        return false;
    }

    return true;
}

int menu_case_multiple(char *fm_filename, char *sm_filename, char *out_filename)
{
    int grc = OKAY;

    matrix_t *first_matrix, *second_matrix;

    if (OKAY != two_file_to_matrices(fm_filename, sm_filename,
    &first_matrix, &second_matrix))
    {
        LOG_ERROR("%s", "<< Unable to allocate matrices");
        return ALLOCATION_FAULT;
    }

    if (is_matrixes_suit_for_multipe(first_matrix, second_matrix))
    {
        matrix_t *product_matrix = get_double_matrix_product(first_matrix,
        second_matrix);

        if (product_matrix)
        {
            if (OKAY == double_matrix_to_file(product_matrix, out_filename))
            {
                LOG_INFO("%s", "Menu case multiple ended success");
            }
            else
            {
                LOG_ERROR("Printing to %s failed", out_filename);
                grc = PRINT_FAILED;
            }

            matrix_free(product_matrix);
        }
        else
        {
            LOG_ERROR("%s", "<< Unable to allocate sum matrix");
            grc = ALLOCATION_FAULT;
        }
    }
    else
    {
        LOG_ERROR("%s", "<< Matrices is not suite for sum");
        grc = MATRIXES_ISNOT_SUIT;
    }
    
    matrix_free(second_matrix);
    matrix_free(first_matrix);

    return grc;
}

bool is_matrix_suit_for_inverse(matrix_t *matrix)
{
    if (NULL == matrix)
    {
        LOG_ERROR("%s", "<< Matrix ptr is null");

        return false;
    }

    size_t row_count = matrix_get_row_count(matrix);
    size_t col_count = matrix_get_column_count(matrix);

    if (row_count != col_count)
    {
        LOG_ERROR("<< row_count != col_count: %zu vs %zu",
        row_count, col_count);

        return false;
    }
    
    if (!(row_count && col_count))
    {
        LOG_ERROR("<< Matrix size if zero: %zux%zu", row_count, col_count);

        return false;
    }

    return true;
}

int menu_case_inverse(char *in_filename, char *out_filename)
{
    int rc, grc = OKAY;

    matrix_t *matrix = file_to_double_matrix(in_filename);

    if (NULL == matrix)
    {
        LOG_ERROR("%s", ">> Unable to allocate source matrix");
        return ALLOCATION_FAULT;
    }

    if ((is_matrix_suit_for_inverse(matrix)))
    {
        rc = invert_double_matrix(&matrix);

        if (OKAY == rc)
        {
            if (OKAY == double_matrix_to_file(matrix, out_filename))
            {
                LOG_ERROR("%s", "Menu case invert ended success");
            }
            else
            {
                LOG_ERROR("Printing to %s failed", out_filename);
                grc = PRINT_FAILED;
            }
        }
        else
        {
            LOG_ERROR("Not OKAY rc of invert matrix: %d", rc);
            grc = ALLOCATION_FAULT;
        }
    }
    else
    {
        LOG_ERROR("%s", "<< Matrices is not suite for multiple");
        grc = MATRIXES_ISNOT_SUIT;
    }

    matrix_free(matrix);

    return grc;
}

int menu(args_t *args)
{
    int rc, grc = OKAY;

    switch (args->action)
    {
        case 'a':
            LOG_INFO("%s", "Sum matrix case chosen");

            rc = menu_case_sum(args->fm_filename, args->sm_filename,
            args->out_filename);

            if (OKAY != rc)
            {
                LOG_ERROR("%s", "Menu case sum failed");
                grc = MENU_CASE_SUM_FAILED;
            }

            break;
        case 'm':
            LOG_INFO("%s", "Multiple matrix case chosen");

            rc = menu_case_multiple(args->fm_filename, args->sm_filename,
            args->out_filename);

            if (OKAY != rc)
            {
                LOG_ERROR("%s", "Menu case multiple failed");
                grc = MENU_CASE_MULTIPLE_FAILED;
            }

            break;
        case 'o':
            LOG_INFO("%s", "Inverse matrix case chosen");

            rc = menu_case_inverse(args->fm_filename, args->out_filename);

            if (OKAY != rc)
            {
                LOG_ERROR("%s", "Menu case inverse failed");
                grc = MENU_CASE_INVERT_FAILED;
            }

            break;
        default:
            {
                LOG_ERROR("%s", "Never get here");
                grc = NEVER_GET_HERE;
            }
    }

    return grc;
}
