#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <inttypes.h>

// fun process_i
#define INCORRECT_DATA 1

// fun copy_array
#define NEGATIVE_ARRAY_LEN 1

// fun main
#define OKAY 0

// fun count_time
#define N_COUNT 4
#define ARR_LEN_COUNT 5
#define PROCESS_COUNT 3
#define MAX_ARRAY_LEN 100000

const int n_arr[N_COUNT] = {10, 100, 1000, 10000};
const int len_arr[ARR_LEN_COUNT] = {10, 100, 1000, 10000, 100000};

int process_1(const float *arr, const int arr_len, float *max_sum)
{
    if (arr_len < 0)
        return NEGATIVE_ARRAY_LEN;

    for (int i = 0; i <= arr_len / 2; ++i)
        if (0 == i || arr[i] + arr[arr_len - i - 1] > *max_sum)
            *max_sum = arr[i] + arr[arr_len - i - 1];

    return OKAY;
}

int process_2(const float *arr, const int arr_len, float *max_sum)
{
    if (arr_len < 0)
        return NEGATIVE_ARRAY_LEN;

    for (int i = 0; i <= arr_len / 2; ++i)
        if (0 == i || *(arr + i) + *(arr - i - 1) > *max_sum)
            *max_sum = *(arr + i) + *(arr - i - 1);

    return OKAY;
}

int process_3(const float *p_start, const float *p_end, float *max_sum)
{
    if (p_start >= p_end)
        return INCORRECT_DATA;

    float *p_s = (float *) p_start, *p_e = (float *) p_end - 1;
    for (; p_s <= p_e; ++p_s, --p_e)
        if (p_start == p_s || *p_s + *p_e > *max_sum)
            *max_sum = *p_s + *p_e;

    return OKAY;
}

int form_random_array(float *arr, const int arr_len)
{
    if (arr_len < 0)
        return NEGATIVE_ARRAY_LEN;

    for (int i = 0; i < arr_len; ++i)
        arr[i] = rand() / (float) RAND_MAX + rand();
    
    return OKAY;
}

int count_time(int64_t sum_time_arr[N_COUNT][ARR_LEN_COUNT][PROCESS_COUNT])
{
    float arr[MAX_ARRAY_LEN];
    form_random_array(arr, MAX_ARRAY_LEN);

    struct timeval tv_start, tv_stop;
    int64_t elapsed_time;

    for (int i = 0; i < ARR_LEN_COUNT; ++i)
    {
        int arr_len = len_arr[i];

        for (int j = 0; j < N_COUNT; ++j)
        {
            int n = n_arr[j];

            for (int k = 0; k < n; ++k)
            {
                float max_sum = 0;
                gettimeofday(&tv_start, NULL);
                process_1(arr, arr_len, &max_sum);
                gettimeofday(&tv_stop, NULL);

                elapsed_time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
                (tv_stop.tv_usec - tv_start.tv_usec);

                sum_time_arr[j][i][0] += elapsed_time;


                max_sum = 0;
                gettimeofday(&tv_start, NULL);
                process_2(arr, arr_len, &max_sum);
                gettimeofday(&tv_stop, NULL);

                elapsed_time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
                (tv_stop.tv_usec - tv_start.tv_usec);

                sum_time_arr[j][i][1] += elapsed_time;


                max_sum = 0;
                gettimeofday(&tv_start, NULL);
                float *p_start = arr, *p_end = arr + arr_len;
                process_3(p_start, p_end, &max_sum);
                gettimeofday(&tv_stop, NULL);

                elapsed_time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
                (tv_stop.tv_usec - tv_start.tv_usec);

                sum_time_arr[j][i][2] += elapsed_time;
            }  
        }
    }
    return OKAY;
}

int print_sum_time_arr(
    int64_t sum_time_arr[N_COUNT][ARR_LEN_COUNT][PROCESS_COUNT])
{
    printf("Summary time\n");
    printf("%5s %7s %20s %20s %20s\n", "N", "Array", "a[i]", "*(a + i)", "*pa");
    for (int i = 0; i < N_COUNT; ++i)
        for (int j = 0; j < ARR_LEN_COUNT; ++j)
            printf("%5d %7d %20ld %20ld %20ld\n", n_arr[i], len_arr[j], 
            sum_time_arr[i][j][0], sum_time_arr[i][j][1],
            sum_time_arr[i][j][2]);

    printf("\n\n\n");

    printf("Average time\n");
    printf("%5s %7s %20s %20s %20s\n", "N", "Array", "a[i]", "*(a + i)", "*pa");
    for (int i = 0; i < N_COUNT; ++i)
        for (int j = 0; j < ARR_LEN_COUNT; ++j)
            printf("%5d %7d %20.5f %20.5f %20.5f\n", n_arr[i], len_arr[j], 
            sum_time_arr[i][j][0] / (float) n_arr[i],
            sum_time_arr[i][j][1] / (float) n_arr[i],
            sum_time_arr[i][j][2] / (float) n_arr[i]);

    return OKAY;
}

void def_zero_value(int64_t sum_time_arr[N_COUNT][ARR_LEN_COUNT][PROCESS_COUNT])
{
    for (int i = 0 ; i < N_COUNT; ++i)
        for (int j = 0; j < ARR_LEN_COUNT; ++j)
            for (int k = 0; k < PROCESS_COUNT; ++k)
                sum_time_arr[i][j][k] = 0;
}

int main(void)
{
    int64_t sum_time_arr[N_COUNT][ARR_LEN_COUNT][PROCESS_COUNT];
    
    def_zero_value(sum_time_arr);

    count_time(sum_time_arr);

    print_sum_time_arr(sum_time_arr);

    return 0;
}