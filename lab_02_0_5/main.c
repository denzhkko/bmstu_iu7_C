#include <stdio.h>
#include <stdlib.h>

#define MIN_ARRAY_LEN 1
#define MAX_ARRAY_LEN 10

// fun input_array
#define INCORRECT_DATA -1
#define INCORRECT_INPUT_ARRAY_LEN -2
#define NOT_ENOUGH_ELEM -3

// fun main
#define OKAY 0
#define INCORRECT_DATA_ERROR 1
#define INCORRECT_INPUT_ARRAY_LEN_ERROR 2
#define NOT_ENOUGH_ELEM_ERROR 3
#define INCORRECT_OUTPUT_DATA_ERROR 2

int input_array(float *p_start, float **p_end)
{
    int arr_len;
    int rc = scanf("%d", &arr_len);

    if (1 != rc)
        return INCORRECT_DATA;

    if (arr_len < MIN_ARRAY_LEN || arr_len > MAX_ARRAY_LEN)
        return INCORRECT_INPUT_ARRAY_LEN;

    *p_end = p_start + arr_len;

    for (float *p = p_start; p < *p_end; ++p)
    {
        rc = scanf("%f", p);
        if (rc != 1)
        {
            char c;
            rc = scanf("%c", &c);
            if (1 == rc && c != ' ' && c != '\n')
                return INCORRECT_DATA;

            return NOT_ENOUGH_ELEM;
        }
    }

    return 0;
}

int search_max_sum(const float *p_start, const float *p_end, float *max_sum)
{
    if (p_start >= p_end)
        return INCORRECT_DATA;

    float *p_s = (float *) p_start, *p_e = (float *) p_end - 1;
    for (; p_s <= p_e; ++p_s, --p_e)
        if (p_start == p_s || *p_s + *p_e > *max_sum)
            *max_sum = *p_s + *p_e;

    return OKAY;
}

int main(void)
{
    float arr[2 * MAX_ARRAY_LEN];

    float *p_start = arr, *p_end = NULL;

    int input_array_res = input_array(p_start, &p_end);

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
            break;
    }

    float max_sum;
    int search_max_sum_res = search_max_sum(p_start, p_end, &max_sum);

    if (INCORRECT_DATA == search_max_sum_res)
    {
        printf("Incorrect output data\n");
        return INCORRECT_OUTPUT_DATA_ERROR;
    }

    printf("%.5f\n", max_sum);

    return OKAY;
}