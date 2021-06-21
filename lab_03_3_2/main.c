#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MIN_AXIS_LEN 1
#define MAX_AXIS_LEN 10

// fun input_2dem_array
#define INCORRECT_DATA 1
#define INCORRECT_ARRAY_SIZE 2
#define NOT_ENOUGH_ELEM 3

// fun input_digit
#define IS_NOT_DIGIT 4

// fun delete_column
#define INCORRECT_COLUMN_INDEX 1

// fun print_array
#define EMPTY_ARRAY 1

// fun main
#define OKAY 0
#define INCORRECT_DATA_ERROR 1
#define INCORRECT_ARRAY_SIZE_ERROR 2
#define NOT_ENOUGH_ELEM_ERROR 3
#define IS_NOT_DIGIT_ERROR 4
#define EMPTY_ARRAY_ERROR 5
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

int input_digit(int *const digit)
{
    int rc = scanf("%d", digit);

    if (1 != rc)
        return INCORRECT_DATA;

    if (*digit < 0 || *digit > 9)
        return IS_NOT_DIGIT;

    return OKAY;
}

int check_error_input_digit(const int exit_code)
{
    switch (exit_code)
    {
        case INCORRECT_DATA:
            fprintf(stderr, "Incorrect data\n");
            return INCORRECT_DATA_ERROR;
        case IS_NOT_DIGIT:
            fprintf(stderr, "Is not digit\n");
            return IS_NOT_DIGIT_ERROR;
        case OKAY:
            return OKAY;
        default:
            fprintf(stderr, "Unknown error\n");
            return UNKNOWN_ERROR;
    }
}

int has_digit(int number, const int digit)
{
    number = abs(number);

    if (number == 0 && digit == 0)
        return TRUE;

    while (number)
    {
        int last_digit = number % 10;
        
        if (digit == last_digit)
            return TRUE;
        
        number /= 10;
    }
    return FALSE;
}

int delete_column(int (*arr)[MAX_AXIS_LEN], const int row_count, 
const int column_count, const int column_index)
{
    if (column_index < 0 || column_index + 1 > column_count)
        return INCORRECT_COLUMN_INDEX;

    for (int i = 0; i < row_count; ++i)
        for (int j = column_index; j < column_count - 1; ++j)
            arr[i][j] = arr[i][j + 1];

    return OKAY;
}

int delete_column_with_digit(int (*arr)[MAX_AXIS_LEN], const int row_count, 
int *column_count, const int digit)
{
    if (row_count < MIN_AXIS_LEN || row_count > MAX_AXIS_LEN || 
    *column_count < MIN_AXIS_LEN || *column_count > MAX_AXIS_LEN)
        return INCORRECT_ARRAY_SIZE;

    if (digit < 0 || digit > 9)
        return IS_NOT_DIGIT;

    next_column: for (int j = *column_count - 1; j >= 0; --j)
        for (int i = 0; i < row_count; ++i)
            if (has_digit(arr[i][j], digit))
            {
                delete_column(arr, row_count, *column_count, j);
                --*column_count;
                --j;
                goto next_column;
            }

    return OKAY;
}

int check_error_delete_column_with_digit(const int exit_code)
{
    switch (exit_code)
    {
        case OKAY:
            return OKAY;
        case INCORRECT_ARRAY_SIZE:
            fprintf(stderr, "Incorrect array size\n");
            return INCORRECT_ARRAY_SIZE_ERROR;
        case IS_NOT_DIGIT:
            fprintf(stderr, "IS not digit\n");
            return IS_NOT_DIGIT_ERROR;
        default:
            fprintf(stderr, "Unknown error\n");
            return UNKNOWN_ERROR;
    }
}

int print_2dem_array(const int (*const arr)[MAX_AXIS_LEN], const int row_count, 
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

    int digit;

    fun_exit_code = input_digit(&digit);
    if (OKAY != (check_fun_exit_code = check_error_input_digit(fun_exit_code)))
        return check_fun_exit_code;

    fun_exit_code = delete_column_with_digit(arr, row_count, &column_count, 
    digit);
    if (OKAY != (check_fun_exit_code = check_error_delete_column_with_digit(
    fun_exit_code)))
        return check_fun_exit_code;

    fun_exit_code = print_2dem_array((const int (*)[MAX_AXIS_LEN]) arr,
    row_count, column_count);
    if (OKAY != (check_fun_exit_code = check_error_print_2dem_array(
    fun_exit_code)))
        return check_fun_exit_code;

    return OKAY;
}