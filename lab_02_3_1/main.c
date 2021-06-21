#include <stdio.h>
#include <math.h>

#define MIN_ARRAY_LEN 1
#define MAX_ARRAY_LEN 10
#define REAL_TOL 1e-6

// fun input_array
#define INCORRECT_DATA -1
#define INCORRECT_ARRAY_LEN -2
#define NOT_ENOUGH_ELEM -3

// fun geometric_mean_of_positive
#define NO_POSITIVE_ELEM -2.0

// fun main
#define OKAY 0
#define INCORRECT_DATA_ERROR 1
#define INCORRECT_ARRAY_LEN_ERROR 2
#define NOT_ENOUGH_ELEM_ERROR 3
#define NO_POSITIVE_ELEM_ERROR 4

int input_array(float *arr)
{
    int arr_len;
    int rc = scanf("%d", &arr_len);

    if (1 != rc)
        return INCORRECT_DATA;

    if (arr_len < MIN_ARRAY_LEN || arr_len > MAX_ARRAY_LEN)
        return INCORRECT_ARRAY_LEN;

    for (int i = 0; i < arr_len; ++i)
    {
        rc = scanf("%f", &arr[i]);
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

float geometric_mean_of_positive(const float *arr, const int arr_len)
{
    float composition = 1.0;
    int count_positive = 0;

    for (int i = 0; i < arr_len; ++i)
    {
        if (arr[i] > 0.0)
        {
            composition *= arr[i];
            ++count_positive;
        }
    }

    if (0 == count_positive)
        return NO_POSITIVE_ELEM;

    return powf(composition, 1.0 / count_positive);
}

int main(void)
{
    float arr[MAX_ARRAY_LEN], arr_len;
    
    int input_array_res = input_array(arr);
    
    switch (input_array_res)
    {
        case INCORRECT_DATA:
            printf("Incorrect data\n");
            return INCORRECT_DATA_ERROR;
        case INCORRECT_ARRAY_LEN:
            printf("Incorrect array len\n");
            return INCORRECT_ARRAY_LEN_ERROR;
        case NOT_ENOUGH_ELEM:
            printf("Not enough elements\n");
            return NOT_ENOUGH_ELEM_ERROR;
        default:
            arr_len = input_array_res;
            break;
    }
    
    float geomitric_mean_res = geometric_mean_of_positive(arr, arr_len);
    if (fabs(geomitric_mean_res + 2.0) < REAL_TOL)
    {
        printf("No positive elem\n");
        return NO_POSITIVE_ELEM_ERROR;
    }

    float geometric_mean = geomitric_mean_res;

    printf("%.5f\n", geometric_mean);

    return OKAY;
}