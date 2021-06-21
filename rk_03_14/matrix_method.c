#include "matrix_method.h"

int matrix_allocate(matrix_t *matrix, const size_t row_count,
const size_t column_count)
{
    matrix->data = calloc(row_count, sizeof(int *));

    if (!(matrix->data))
        return ALLOCATION_FAILED;

    for (size_t i = 0; i < row_count; ++i)
    {
        matrix->data[i] = calloc(column_count, sizeof(int));
        if (!(matrix->data[i]))
        {
            matrix_free(matrix);
            return ALLOCATION_FAILED;
        }
    }

    matrix->row_count = row_count;
    matrix->column_count = column_count;

    return OKAY;
}

int file_to_matrix(char *filename, matrix_t *matrix)
{
    int rc, grc = OKAY;
    FILE *f = fopen(filename, "r");

    if (f)
    {
        size_t row_count, column_count, num_count;
        if (3 != fscanf(f, "%zu%zu%zu", &row_count, &column_count, &num_count))
            return INCORRECT_FILE;

        rc = matrix_allocate(matrix, row_count, column_count);

        if (OKAY != rc)
            return rc;

        for (size_t row_i = 0; row_i < row_count; ++row_i)
        {
            size_t i, j, value;

            rc = fscanf(f, "%zu%zu%zu", &i, &j, &value);
            
            if (3 != rc)
                return INCORRECT_FILE;

            matrix->data[i][j] = value;
        }

        fclose(f);
    }
    else
    {
        fprintf(stderr, "File not found");
        grc = FILE_NOT_FOUND;
    }

    return grc;
}

void matrix_free(matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->row_count; ++i)
        free(matrix->data[i]);

    free(matrix->data);
}

void saper(matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->row_count; ++i)
        for (size_t j = 0; j < matrix->column_count; ++j)
        {
            if (0 == matrix->data[i][j])
            {
                int count = 0;

                COUNT_PLUS(i - 1, j - 1);
                COUNT_PLUS(i - 1, j);
                COUNT_PLUS(i - 1, j + 1);
                COUNT_PLUS(i, j - 1);
                COUNT_PLUS(i, j + 1);
                COUNT_PLUS(i + 1, j - 1);
                COUNT_PLUS(i + 1, j);
                COUNT_PLUS(i + 1, j + 1);

                matrix->data[i][j] = count;
                LOG_INFO("matrix->data[%zu][%zu] = %d", i, j, count);
            }
        }
}

void matrix_print(FILE *sourse, matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->row_count; ++i)
    {
        for (size_t j = 0; j < matrix->column_count; ++j)
            fprintf(sourse, "%d ", matrix->data[i][j]);
        fprintf(sourse, "\n");
    }
}

bool is_only_zero_row(matrix_t *matrix, size_t row)
{
    for (int j = 0; j < matrix->column_count; ++j)
        if (0 != matrix->data[row][j])
            return false;

    return true;
}

int delete_rows(matrix_t *matrix)
{
    for (size_t i = matrix->row_count - 1; ; --i)
    {
        if (is_only_zero_row(matrix, i))
        {
            free(matrix->data[i]);

            for (size_t k = i; k < matrix->row_count - 2; ++k)
            {
                matrix->data[k] = matrix->data[k + 1];
            }

            matrix->row_count--;
            if (NULL == realloc(matrix->data, matrix->row_count * sizeof(int *)))
            {
                LOG_ERROR("%s", "Беды с памятью");
                return REALLOCATION_FAILED;
            }

            LOG_DEBUG("matrix->row_count == %zu", matrix->row_count);
        }

        if (0 == i)
            break;
    }

    return OKAY;
}

int matrix_to_file(char *filename, matrix_t *matrix)
{
    FILE *f = fopen(filename, "w");

    if (f)
    {
        matrix_print(f, matrix);
        return OKAY;
    }
    else
    {
        return UNABLE_REWRITE_FILE;
    }
}
