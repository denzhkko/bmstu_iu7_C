#include <stdio.h>
#include <stdlib.h>

#define MIN_AXIS_LEN 1
#define MAX_AXIS_LEN 10

// fun input_2dem_array
#define INCORRECT_DATA 1
#define INCORRECT_ARRAY_SIZE 2
#define NOT_ENOUGH_ELEM 3

// fun slice_digit_sum_more_10_elem
#define SLICE_NUM 3
#define ZERO_LEN_ARRAY 1

// fun print_array
#define EMPTY_ARRAY 1

// fun main
#define OKAY 0
#define INCORRECT_DATA_ERROR 1
#define INCORRECT_ARRAY_SIZE_ERROR 2
#define NOT_ENOUGH_ELEM_ERROR 3
#define EMPTY_ARRAY_ERROR 4
#define ZERO_LEN_ARRAY_ERROR 5
#define UNKNOWN_ERROR 6


int input_2dem_array(int (*const arr)[MAX_AXIS_LEN], int *const row_count,
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
            rc = scanf("%d", &arr[i][j]);
            
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

int digit_sum(int number)
{
    number = abs(number);

    int sum = 0;
    while (number)
    {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

int slice_digit_sum_more_10_elem(int (*mat)[MAX_AXIS_LEN],
const int row_count, int column_count)
{
    if (row_count < MIN_AXIS_LEN || row_count > MAX_AXIS_LEN || 
    column_count < MIN_AXIS_LEN || column_count > MAX_AXIS_LEN)
        return INCORRECT_ARRAY_SIZE;

    int arr_len = 0;
    int arr[MAX_AXIS_LEN * MAX_AXIS_LEN];
    
    for (int i = 0; i < row_count; ++i)
        for (int j = 0; j < column_count; ++j)
            if (digit_sum(mat[i][j]) > 10)
                arr[arr_len++] = mat[i][j];

    if (0 == arr_len)
        return ZERO_LEN_ARRAY;

    for (int num = 0; num < SLICE_NUM; ++num)
    {
        int k = arr[0];
        for (int i = 0; i < arr_len - 1; ++i)
            arr[i] = arr[i + 1];
        arr[arr_len - 1] = k;
    }


    int arr_index = 0;
    for (int i = 0; i < row_count; ++i)
        for (int j = 0; j < column_count; ++j)
            if (digit_sum(mat[i][j]) > 10)
                mat[i][j] = arr[arr_index++];

    return OKAY;
}

int check_error_slice_digit_sum_more_10_elem(const int exit_code)
{
    switch (exit_code)
    {
        case OKAY:
            return OKAY;
        case INCORRECT_ARRAY_SIZE:
            fprintf(stderr, "Incorrect array size\n");
            return INCORRECT_ARRAY_SIZE_ERROR;
        case ZERO_LEN_ARRAY:
            fprintf(stderr, "Zero array len\n");
            return ZERO_LEN_ARRAY_ERROR;
        default:
            fprintf(stderr, "Unknown error\n");
            return UNKNOWN_ERROR;
    }
}

int print_2dem_array(const int (*const arr)[MAX_AXIS_LEN], 
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
            printf("%d ", arr[i][j]);
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
    int arr[MAX_AXIS_LEN][MAX_AXIS_LEN];

    fun_exit_code = input_2dem_array(arr, &row_count, &column_count);
    if (OKAY != (check_fun_exit_code = check_error_input_2dem_array(
    fun_exit_code)))
        return check_fun_exit_code;

    fun_exit_code = slice_digit_sum_more_10_elem(arr, row_count, column_count);
    if (OKAY != (check_fun_exit_code = check_error_slice_digit_sum_more_10_elem(
    fun_exit_code)))
        return check_fun_exit_code;

    fun_exit_code = print_2dem_array((const int (*)[MAX_AXIS_LEN]) arr,
    row_count, column_count);
    if (OKAY != (check_fun_exit_code = check_error_print_2dem_array(
    fun_exit_code)))
        return check_fun_exit_code;

    return OKAY;
}