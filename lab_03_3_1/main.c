#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define MIN_AXIS_LEN 1
#define MAX_AXIS_LEN 10

// fun input_2dem_array
#define INCORRECT_DATA 1
#define INCORRECT_ARRAY_SIZE 2
#define NOT_ENOUGH_ELEM 3

// fun main
#define OKAY 0
#define INCORRECT_DATA_ERROR 1
#define INCORRECT_ARRAY_SIZE_ERROR 2
#define NOT_ENOUGH_ELEM_ERROR 3
#define UNKNOWN_ERROR 4

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
        case INCORRECT_DATA:
            fprintf(stderr, "Incorrect data\n");
            return INCORRECT_DATA_ERROR;
        case INCORRECT_ARRAY_SIZE:
            fprintf(stderr, "Incorrect array size\n");
            return INCORRECT_ARRAY_SIZE_ERROR;
        case NOT_ENOUGH_ELEM:
            fprintf(stderr, "Not enough elem\n");
            return NOT_ENOUGH_ELEM_ERROR;
        case OKAY:
            return OKAY;
        default:
            fprintf(stderr, "Unknown error\n");
            return UNKNOWN_ERROR;
    }
}

int is_non_growing_seq(const float *const seq, const int len)
{
    if (len <= 1)
        return FALSE;

    for (int i = 1; i < len; ++i)
        if (seq[i - 1] < seq[i])
            return FALSE;
    return TRUE;
}

int is_non_decreasing_seq(const float *const seq, const int len)
{
    if (len <= 1)
        return FALSE;

    for (int i = 1; i < len; ++i)
        if (seq[i - 1] > seq[i])
            return FALSE;
    return TRUE;
}

int is_mono_seq(const float *const seq, const int len)
{
    if (is_non_growing_seq(seq, len))
        return TRUE;

    if (is_non_decreasing_seq(seq, len))
        return TRUE;

    return FALSE;
}

int mono_seq_arr(const float (*const arr)[MAX_AXIS_LEN], const int row_count, 
const int column_count, int *const mono_arr)
{
    if (row_count < MIN_AXIS_LEN || row_count > MAX_AXIS_LEN || 
    column_count < MIN_AXIS_LEN || column_count > MAX_AXIS_LEN)
        return INCORRECT_ARRAY_SIZE;

    for (int k = 0; k < row_count; ++k)
    {
        if (is_mono_seq(&arr[k][0], column_count))
            mono_arr[k] = 1;
        else
            mono_arr[k] = 0;
    }
    return OKAY;
}

int check_error_mono_seq_arr(const int exit_code)
{
    switch (exit_code)
    {
        case INCORRECT_ARRAY_SIZE:
            fprintf(stderr, "Incorrect array size");
            return INCORRECT_ARRAY_SIZE_ERROR;
        case OKAY:
            return OKAY;
        default:
            fprintf(stderr, "Unknown error\n");
            return UNKNOWN_ERROR;
    }
}

int print_1dem_array(const int *const arr, const int len)
{
    if (len <= 0)
        return INCORRECT_ARRAY_SIZE;

    for (int i = 0; i < len; ++i)
        printf("%d ", arr[i]);
    printf("\n");

    return OKAY;
}

int check_error_print_1dem_array(const int exit_code)
{
    switch (exit_code)
    {
        case INCORRECT_ARRAY_SIZE:
            fprintf(stderr, "Incorrect array size\n");
            return INCORRECT_ARRAY_SIZE_ERROR;
        case OKAY:
            return OKAY;
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

    int mono_arr[MAX_AXIS_LEN];

    fun_exit_code = mono_seq_arr((const float (*)[MAX_AXIS_LEN]) arr, row_count,
    column_count, mono_arr);
    if (OKAY != (check_fun_exit_code = check_error_mono_seq_arr(fun_exit_code)))
        return check_fun_exit_code;

    fun_exit_code = print_1dem_array(mono_arr, row_count);
    if (OKAY != (check_fun_exit_code = check_error_print_1dem_array(
    fun_exit_code)))
        return check_fun_exit_code;

    return OKAY;
}