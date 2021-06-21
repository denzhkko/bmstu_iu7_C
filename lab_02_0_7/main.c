#include <stdio.h>
#include <stdlib.h>

#define MIN_ARRAY_LEN 1
#define MAX_ARRAY_LEN 100000

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


#define INCORRECT_OUTPUT_ARRAY_LEN_ERROR 5

int input_array(long double *arr)
{
    int arr_len;
    int rc = scanf("%d", &arr_len);

    if (1 != rc)
        return INCORRECT_DATA;

    if (arr_len < MIN_ARRAY_LEN || arr_len > MAX_ARRAY_LEN)
        return INCORRECT_INPUT_ARRAY_LEN;

    for (int i = 0; i < arr_len; ++i)
    {
        rc = scanf("%Lf", &arr[i]);
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

void bubble_sort(long double *arr, const int arr_len)
{
    for (int i = arr_len - 1; i > 0; --i)
        for (int j = 0; j < i; ++j)
            if (arr[j] > arr[j + 1])
            {
                long double k = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = k;
            }
}

int print_array(const long double *arr, const int arr_len)
{
    if (arr_len < 0)
        return INCORRECT_OUTPUT_ARRAY_LEN;

    for (int i = 0; i < arr_len; ++i)
        printf("%.5Lf\n", arr[i]);

    return OKAY;
}

int main(void)
{
    long double arr[MAX_ARRAY_LEN], arr_len;

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

    bubble_sort(arr, arr_len);

    int print_array_res = print_array(arr, arr_len);

    if (INCORRECT_OUTPUT_ARRAY_LEN == print_array_res)
    {
        printf("Incorrect output array len\n");
        return INCORRECT_OUTPUT_ARRAY_LEN_ERROR;
    }

    return OKAY;
}