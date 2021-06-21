#include <stdio.h>

#define MIN_AXIS_LEN 1
#define MAX_AXIS_LEN 10

// fun input_2dem_array
#define INCORRECT_DATA 1
#define INCORRECT_ARRAY_SIZE 2
#define NOT_ENOUGH_ELEM 3

// fun print_array
#define EMPTY_ARRAY 1

// fun min_in_seq
#define INCORRECT_SEQ_LEN 5

// fun main
#define OKAY 0
#define INCORRECT_DATA_ERROR 1
#define INCORRECT_ARRAY_SIZE_ERROR 2
#define NOT_ENOUGH_ELEM_ERROR 3
#define EMPTY_ARRAY_ERROR 4
#define INCORRECT_SEQ_LEN_ERROR 5
#define UNKNOWN_ERROR 6

int input_2dem_array(float (*const arr)[MAX_AXIS_LEN], int *const row_count,
int *const column_count)
{
    int rc = scanf("%d%d", row_count, column_count);

    if (2 != rc)
        return INCORRECT_DATA;
    
    if (*row_count < MIN_AXIS_LEN || *row_count > MAX_AXIS_LEN || 
    *column_count < MIN_AXIS_LEN || *column_count > MAX_AXIS_LEN)
        return INCORRECT_ARRAY_SIZE;

    for (int i = 0; i < *row_count; ++i)
        for (int j = 0; j < *column_count; ++j)
        {
            rc = scanf("%f", &arr[i][j]);
            
            if (rc != 1)
            {
                char c;
                rc = scanf("%c", &c);

                if (rc == 1 && c != ' ' && c != '\n')
                    return INCORRECT_DATA;
                
                return NOT_ENOUGH_ELEM;
            }
        }

    return OKAY;
}

int check_error_input_2dem_array(const int exit_code)
{
    switch (exit_code)
    {
        case OKAY:
            return OKAY;
        case INCORRECT_DATA:
            fprintf(stderr, "Incorrect data\n");
            return INCORRECT_DATA_ERROR;
        case INCORRECT_ARRAY_SIZE:
            fprintf(stderr, "Incorrect array size\n");
            return INCORRECT_ARRAY_SIZE_ERROR;
        case NOT_ENOUGH_ELEM:
            fprintf(stderr, "Not enough elem\n");
            return NOT_ENOUGH_ELEM_ERROR;
        default:
            fprintf(stderr, "Unknown error\n");
            return UNKNOWN_ERROR;
    }
}

int min_in_seq(const float *const seq, const int len, float *const min)
{
    if (len <= 0)
        return INCORRECT_SEQ_LEN;

    *min = seq[0];

    for (int i = 1; i < len; ++i)
        if (seq[i] < *min)
            *min = seq[i];

    return OKAY;
}

int swap_neighboring_rows(float (*const arr)[MAX_AXIS_LEN], 
const int row_count, const int column_count, const int row_index)
{
    if (row_count < MIN_AXIS_LEN || row_count > MAX_AXIS_LEN || 
    column_count < MIN_AXIS_LEN || column_count > MAX_AXIS_LEN)
        return INCORRECT_ARRAY_SIZE;

    if (row_index + 2 > row_count)
        return INCORRECT_ARRAY_SIZE;    

    for (int j = 0; j < column_count; ++j)
    {
        float k = arr[row_index][j];
        arr[row_index][j] = arr[row_index + 1][j];
        arr[row_index + 1][j] = k;
    }

    return OKAY;
}

int sort_by_min_in_row(float (*arr)[MAX_AXIS_LEN], const int row_count, 
int column_count)
{
    if (row_count < MIN_AXIS_LEN || row_count > MAX_AXIS_LEN || 
    column_count < MIN_AXIS_LEN || column_count > MAX_AXIS_LEN)
        return INCORRECT_ARRAY_SIZE;

    for (int i = row_count - 1; i > 0; --i)
        for (int j = 0; j < i; ++j)
        {
            float min_in_j_row;
            min_in_seq(&arr[j][0], column_count, &min_in_j_row);

            float min_in_j_plus_1_row;
            min_in_seq(&arr[j + 1][0], column_count, &min_in_j_plus_1_row);

            if (min_in_j_row < min_in_j_plus_1_row)
            {
                int fun_exit_code = swap_neighboring_rows(arr, row_count, 
                column_count, j);
                
                if (OKAY != fun_exit_code)
                    return fun_exit_code;
            }
        }

    return OKAY;
}

int check_error_sort_by_min_in_row(const int exit_code)
{
    switch (exit_code)
    {
        case OKAY:
            return OKAY;
        case INCORRECT_ARRAY_SIZE:
            fprintf(stderr, "Incorrect array size");
            return INCORRECT_ARRAY_SIZE_ERROR;
        default:
            fprintf(stderr, "Unknown error\n");
            return UNKNOWN_ERROR;
    }
}

int print_2dem_array(const float (*const arr)[MAX_AXIS_LEN], const int row_count, 
const int column_count)
{
    if (0 == row_count || 0 == column_count)
        return EMPTY_ARRAY;

    if (row_count < MIN_AXIS_LEN || row_count > MAX_AXIS_LEN || 
    column_count < MIN_AXIS_LEN || column_count > MAX_AXIS_LEN)
        return INCORRECT_ARRAY_SIZE;

    for (int i = 0; i < row_count; ++i)
    {
        for (int j = 0; j < column_count; ++j)
            printf("%.5f ", arr[i][j]);
        printf("\n");
    }

    return OKAY;
}

int check_error_print_2dem_array(const int exit_code)
{
    switch (exit_code)
    {
        case OKAY:
            return OKAY;
        case EMPTY_ARRAY:
            fprintf(stderr, "Empty array\n");
            return EMPTY_ARRAY_ERROR;
        case INCORRECT_ARRAY_SIZE:
            fprintf(stderr, "Incorrect array size\n");
            return INCORRECT_ARRAY_SIZE_ERROR;
        default:
            fprintf(stderr, "Unknown error\n");
            return UNKNOWN_ERROR;
    }
}

int main(void)
{
    int check_fun_exit_code, fun_exit_code;

    int row_count, column_count;
    float arr[MAX_AXIS_LEN][MAX_AXIS_LEN];

    fun_exit_code = input_2dem_array(arr, &row_count, &column_count);
    if (OKAY != (check_fun_exit_code = check_error_input_2dem_array(
    fun_exit_code)))
        return check_fun_exit_code;

    fun_exit_code = sort_by_min_in_row(arr, row_count, column_count);
    if (OKAY != (check_fun_exit_code = check_error_sort_by_min_in_row(
    fun_exit_code)))
        return check_fun_exit_code;

    fun_exit_code = print_2dem_array((const float (*)[MAX_AXIS_LEN]) arr,
    row_count, column_count);
    if (OKAY != (check_fun_exit_code = check_error_print_2dem_array(
    fun_exit_code)))
        return check_fun_exit_code;

    return OKAY;
}