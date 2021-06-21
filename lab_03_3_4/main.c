#include <stdio.h>

#define MIN_AXIS_LEN 1
#define MAX_AXIS_LEN 10

// fun input_2dem_array
#define INCORRECT_DATA 1
#define INCORRECT_ARRAY_SIZE 2
#define NOT_ENOUGH_ELEM 3

// fun print_array
#define EMPTY_ARRAY 1

// fun main
#define OKAY 0
#define INCORRECT_DATA_ERROR 1
#define INCORRECT_ARRAY_SIZE_ERROR 2
#define NOT_ENOUGH_ELEM_ERROR 3
#define EMPTY_ARRAY_ERROR 4
#define NOT_SQU_ARR_ERROR 5
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

int check_valid_sqr_array(const float row_count, const float column_count)
{
    if (row_count < MIN_AXIS_LEN || row_count > MAX_AXIS_LEN || 
    column_count < MIN_AXIS_LEN || column_count > MAX_AXIS_LEN)
    {
        fprintf(stderr, "Incorrect array size\n");
        return INCORRECT_ARRAY_SIZE_ERROR;
    }

    if (row_count != column_count)
    {
        fprintf(stderr, "Not a square array\n");
        return NOT_SQU_ARR_ERROR;
    }

    return OKAY;
}

int replace_elem(float (*arr)[MAX_AXIS_LEN], const int row_count, 
int column_count)
{
    if (row_count < MIN_AXIS_LEN || row_count > MAX_AXIS_LEN || 
    column_count < MIN_AXIS_LEN || column_count > MAX_AXIS_LEN)
        return INCORRECT_ARRAY_SIZE;

    for (int j = 0; j < column_count; ++j)
        for (int i = j; i < row_count - j; ++i)
        {
            float k = arr[i][j];
            arr[i][j] = arr[i][column_count - 1 - j];
            arr[i][column_count - 1 - j] = k;
        }

    return OKAY;
}

int check_error_replace_elem(const int exit_code)
{
    switch (exit_code)
    {
        case OKAY:
            return OKAY;
        case INCORRECT_ARRAY_SIZE:
            fprintf(stderr, "Incorrect array size\n");
            return INCORRECT_ARRAY_SIZE_ERROR;
        default:
            fprintf(stderr, "Unknown error\n");
            return UNKNOWN_ERROR;
    }
}

int print_2dem_array(const float (*const arr)[MAX_AXIS_LEN], 
const int row_count, const int column_count)
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

    if (OKAY != (fun_exit_code = check_valid_sqr_array(row_count, column_count)))
        return fun_exit_code;

    fun_exit_code = replace_elem(arr, row_count, column_count);
    if (OKAY != (check_fun_exit_code = check_error_replace_elem(
    fun_exit_code)))
        return check_fun_exit_code;

    fun_exit_code = print_2dem_array((const float (*)[MAX_AXIS_LEN]) arr,
    row_count, column_count);
    if (OKAY != (check_fun_exit_code = check_error_print_2dem_array(
    fun_exit_code)))
        return check_fun_exit_code;

    return OKAY;
}