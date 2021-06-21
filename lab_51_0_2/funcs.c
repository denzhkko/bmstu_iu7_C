#include "funcs.h"

int find_avg_value(FILE *f, float *avg)
{
    rewind(f);

    int rc = 0;
    int num_count = 0;
    float sum = 0.0, num;

    while (1 == (rc = fscanf(f, "%f", &num)))
    {
        sum += num;
        ++num_count;
    }

    char c;
    if (1 == (rc = fscanf(f, "%c", &c)))
        return INCORRECT_SYMBOL;

    if (0 == num_count)
        return NOT_ENOUGH_NUM;

    *avg = sum / num_count;
    return OKAY;
}

int find_similar(FILE *f, const float avg, float *similar)
{
    fseek(f, 0, SEEK_SET);

    int rc = 0;
    float num;

    if (1 == (rc = fscanf(f, "%f", &num)))
        *similar = num;
    else
        return NOT_ENOUGH_NUM;

    while (1 == (rc = fscanf(f, "%f", &num)))
        if (fabs(avg - *similar) > fabs(avg - num))
            *similar = num;

    char c;

    if (1 == (rc = fscanf(f, "%c", &c)))
        return INCORRECT_SYMBOL;

    return OKAY;
}
