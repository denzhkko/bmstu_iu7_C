#include <stdio.h>

#define MIN_ARRAY_LEN 1
#define MAX_ARRAY_LEN 10

#define TRUE 1
#define FALSE 0

// fun input_array
#define INCORRECT_DATA -1
#define INCORRECT_INPUT_ARRAY_LEN -2
#define NOT_ENOUGH_ELEM -3

// fun int_power
#define NEGATIVE_POWER -1

// fun make_armstrong_array
#define NO_ARMSTRONG_NUM -1

// fun print_array
#define INCORRECT_OUTPUT_ARRAY_LEN 1

// fun main
#define OKAY 0
#define INCORRECT_DATA_ERROR 1
#define INCORRECT_INPUT_ARRAY_LEN_ERROR 2
#define NOT_ENOUGH_ELEM_ERROR 3
#define NO_ARMSTRONG_NUM_ERROR 4
#define INCORRECT_OUTPUT_ARRAY_LEN_ERROR 5

int input_array(int *arr)
{
    int arr_len;
    int rc = scanf("%d", &arr_len);

    if (1 != rc)
        return INCORRECT_DATA;

    if (arr_len < MIN_ARRAY_LEN || arr_len > MAX_ARRAY_LEN)
        return INCORRECT_INPUT_ARRAY_LEN;

    for (int i = 0; i < arr_len; ++i)
    {
        rc = scanf("%d", &arr[i]);
        if (rc != 1)
        {
            char c;
            rc = scanf("%c", &c);
            if (1 == rc && c != ' ' && c != '\n')
                return INCORRECT_DATA;

            return NOT_ENOUGH_ELEM;
        }
    }

    return arr_len;
}

int int_power(const int a, const int n)
{
    if (n < 0)
        return NEGATIVE_POWER;
    
    int res = 1;

    for (int i = 0; i < n; ++i)
        res *= a;

    return res;
}

int is_armstrong_num(const int num)
{
    if (num <= 0)
        return FALSE;

    int copy_num = num;
    int num_len = 0;

    while (copy_num)
    {
        ++num_len;
        copy_num /= 10;
    }

    int sum_cubes = 0;
    copy_num = num;

    while (copy_num)
    {
        int digit = copy_num % 10;
        sum_cubes += int_power(digit, num_len);
        copy_num /= 10;
    }

    if (num == sum_cubes)
        return TRUE;
    return FALSE;
}

int make_armstrong_array(const int *original_arr, const int original_arr_len,
int *armstrong_arr)
{
    int armstrong_arr_len = 0;

    for (int i = 0; i < original_arr_len; ++i)
        if (is_armstrong_num(original_arr[i]))
        {
            armstrong_arr[armstrong_arr_len] = original_arr[i];
            ++armstrong_arr_len;
        }

    if (0 == armstrong_arr_len)
        return NO_ARMSTRONG_NUM;

    return armstrong_arr_len;
}

int print_array(const int *arr, const int arr_len)
{
    if (arr_len < 0)
        return INCORRECT_OUTPUT_ARRAY_LEN;

    for (int i = 0; i < arr_len; ++i)
        printf("%d ", arr[i]);

    return OKAY;
}

int main(void)
{
    int original_arr[MAX_ARRAY_LEN], original_arr_len;

    int input_array_res = input_array(original_arr);

    switch (input_array_res)
    {
        case INCORRECT_DATA:
            printf("Incorrect data\n");
            return INCORRECT_DATA_ERROR;
        case INCORRECT_INPUT_ARRAY_LEN:
            printf("Incorrect array len\n");
            return INCORRECT_INPUT_ARRAY_LEN_ERROR;
        case NOT_ENOUGH_ELEM:
            printf("Not enough elements\n");
            return NOT_ENOUGH_ELEM_ERROR;
        default:
            original_arr_len = input_array_res;
            break;
    }

    int armstrong_arr[MAX_ARRAY_LEN];
    int make_armstrong_array_res = make_armstrong_array(original_arr,
    original_arr_len, armstrong_arr);

    if (NO_ARMSTRONG_NUM == make_armstrong_array_res)
    {
        printf("No armstrong numbers in origin array\n");
        return NO_ARMSTRONG_NUM_ERROR;
    }
    int armstrong_arr_len = make_armstrong_array_res;

    int print_array_res = print_array(armstrong_arr, armstrong_arr_len);

    if (INCORRECT_OUTPUT_ARRAY_LEN == print_array_res)
    {
        printf("Incorrect output array len\n");
        return INCORRECT_OUTPUT_ARRAY_LEN_ERROR;
    }

    return OKAY;
}