#include <stdio.h>

#define MIN_ARR_LEN 0
#define MAX_ARR_LEN 1000

int read_array(int * const arr, int *arr_len)
{
    *arr_len = 0;

    int number;
    int rc = scanf("%d", &number);
    
    while (rc == 1 && *arr_len <= MAX_ARR_LEN && rc != EOF)
    {
        arr[*arr_len] = number;
        (*arr_len)++;

        rc = scanf("%d", &number);
    }

    return 0;
}

int first_pos(const int * const arr, const int arr_len, const int num)
{
    for (int i = 0; i < arr_len; ++i)
        if (num == arr[i])
            return i;
    
    return -1;
}

int count_uniq_pos_el(const int * const arr, const int arr_len)
{
    int count = 0;
    for (int i = 0; i < arr_len; ++i)
        if (arr[i] > 0 && i == first_pos(arr, arr_len, arr[i]))
            ++count;

    return count;
}

int main(void)
{
    int arr_len = 0;
    int arr[MAX_ARR_LEN];

    read_array(arr, &arr_len);

    int count = count_uniq_pos_el(arr, arr_len);

    printf("%d\n", count);

    return 0;
}