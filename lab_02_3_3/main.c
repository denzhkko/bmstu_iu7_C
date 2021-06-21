#include <stdio.h>
#include <stdlib.h>

#define MIN_ARRAY_LEN 1
#define MAX_ARRAY_LEN 10

// fun input_array
#define INCORRECT_DATA -1
#define INCORRECT_INPUT_ARRAY_LEN -2
#define NOT_ENOUGH_ELEM -3

// fun print_array
#define INCORRECT_OUTPUT_ARRAY_LEN 1

// fun main
#define OKAY 0
#define INCORRECT_DATA_ERROR 1
#define INCORRECT_INPUT_ARRAY_LEN_ERROR 2
#define NOT_ENOUGH_ELEM_ERROR 3
#define INCORRECT_OUTPUT_ARRAY_LEN_ERROR 4

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

int print_array(const int *arr, const int arr_len)
{
    if (arr_len < 0)
        return INCORRECT_OUTPUT_ARRAY_LEN;

    for (int i = 0; i < arr_len; ++i)
        printf("%d ", arr[i]);

    return OKAY;
}

int reverse_num(int number)
{
    number = abs(number);
    int res = 0;

    while (number)
    {
        int digit = number % 10;
        res = 10 * res + digit;
        number /= 10;
    }

    return res;
}

void add_reverse_pos_numbers(int *arr, int *arr_len)
{
    for (int i = 0; i < *arr_len; ++i)
        if (arr[i] > 0)
        {
            for (int j = *arr_len; j > i + 1; --j)
                arr[j] = arr[j - 1];
            arr[i + 1] = reverse_num(arr[i]);
            ++i;
            ++*arr_len;
        }
}

int main(void)
{
    int arr[2 * MAX_ARRAY_LEN], arr_len;

    int input_array_res = input_array(arr);

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
            arr_len = input_array_res;
            break;
    }

    add_reverse_pos_numbers(arr, &arr_len);

    int print_array_res = print_array(arr, arr_len);

    if (INCORRECT_OUTPUT_ARRAY_LEN == print_array_res)
    {
        printf("Incorrect output array len\n");
        return INCORRECT_OUTPUT_ARRAY_LEN_ERROR;
    }

    return OKAY;
}