#include <stdio.h>

#define MAX_ARR_LEN 1000

#define MAX_ROW_COUNT 1000
#define MAX_COLUMN_COUNT 30

#define TRUE 1
#define FALSE 0

int read_seq(int * const arr, int *arr_len)
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

int form_matrix(const int * const seq, const int seq_len, 
int matrix[][MAX_COLUMN_COUNT])
{
    for (int i = 0; i < MAX_ROW_COUNT && i < seq_len; ++i)
    {
        int number = seq[i];
        for (int j = 0; j < MAX_COLUMN_COUNT; ++j)
        {
            matrix[i][j] = number % 10;
            number /= 10;
        }
    }

    return 0;
}

int is_even(const int * const arr)
{
    if (arr[0] % 2 == 0) 
        return TRUE;
    return FALSE;
}

int is_less(const int * const seq1, const int * const seq2, const int col_count)
{
    for (int i = col_count - 1; i >= 0; --i)
    {
        if (seq1[i] > seq2[i])
            return FALSE;
        if (seq1[i] < seq2[i])
            return TRUE;
    }

    return FALSE;
}

int search_min_number(int matrix[][MAX_COLUMN_COUNT],
const int row_count, const int col_count)
{
    int row_min = -1;

    for (int i = 0; i < row_count; ++i)
        if (is_even(matrix[i]) && (-1 == row_min || 
        is_less(matrix[i], matrix[row_min], col_count)))
            row_min = i;

    return row_min;
}

int print_market_matrix(int matrix[][MAX_COLUMN_COUNT], const int row_count, 
const int column_count)
{
    int non_zero_count = 0;

    for (int i = 0; i < row_count; ++i)
        for (int j = 0; j < column_count; ++j)
            if (matrix[i][j] != 0)
                ++non_zero_count;

    printf("%d %d %d\n", row_count, column_count, non_zero_count);

    for (int i = 0; i < row_count; ++i)
        for (int j = 0; j < column_count; ++j)
            if (matrix[i][j] != 0)
                printf("%d %d %d\n", i + 1, j + 1, matrix[i][j]);

    return 0;
}

int main(void)
{
    int seq[MAX_ARR_LEN];
    int seq_len = 0;

    read_seq(seq, &seq_len);

    int matrix[MAX_ROW_COUNT][MAX_COLUMN_COUNT];
    int row_count = seq_len, column_count = MAX_COLUMN_COUNT;

    form_matrix(seq, seq_len, matrix);

    int row = search_min_number(matrix, row_count, column_count);
    printf("index of min even number: %d\n", row);

    print_market_matrix(matrix, row_count, column_count);
    return 0;
}