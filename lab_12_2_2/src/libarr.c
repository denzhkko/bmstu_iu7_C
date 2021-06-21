#include "../inc/libarr.h"

void array_fill_fib(int *arr, int arr_len)
{
    for (int i = 0, fib = 1, fib_next = 1; i < arr_len; ++i)
    {
        arr[i] = fib;
        fib_next += fib;
        fib = fib_next - fib;
    }
}

int array_cp_uniq_len(int *arr, int arr_len)
{
    int uniq_len = 0;

    for (int i = 0; i < arr_len; ++i)
    {
        bool is_found = false;

        for (int j = 0; j < i; ++j)
            if (arr[j] == arr[i])
            {
                is_found = true;
                break;
            }

        if (!is_found)
            ++uniq_len;
    }

    return uniq_len;
}

void array_cp_uniq(int *arr, int arr_len, int *arr_uniq, int *arr_uniq_len)
{
    int uniq_len = 0;

    for (int i = 0; i < arr_len; ++i)
    {
        bool is_found = false;

        for (int j = 0; j < uniq_len; ++j)
            if (arr_uniq[j] == arr[i])
            {
                is_found = true;
                break;
            }
        if (!is_found)
            arr_uniq[uniq_len++] = arr[i];
    }

    *arr_uniq_len = uniq_len;
}
