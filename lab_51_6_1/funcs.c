#include <string.h>
#include "funcs.h"

#define MAX(X,Y) (X > Y ? X : Y)

int process(FILE *f, int *max_len)
{
    *max_len = 0;

    int curr_num, prev_num, prev_prev_num;
    int curr_len = 0;
    int rc;

    // read first two numbers
    for (int i = 0; i < 2; ++i)
    {
        rc = fscanf(f, "%d\n", &curr_num);

        if (rc != 1)
            return NOT_ENOUGH_NUM;

        prev_prev_num = prev_num;
        prev_num = curr_num;
    }

    if (prev_prev_num != prev_num)
        curr_len = 2;
 
    while (1 == (rc = fscanf(f, "%d", &curr_num)))
    {
        int is_increasing = (prev_prev_num < prev_num &&
            prev_num < curr_num);
        int is_decreasing = (prev_prev_num > prev_num &&
            prev_num > curr_num);

        if (is_increasing || is_decreasing)
            ++curr_len;
        else if (prev_num != curr_num)
        {
            *max_len = MAX(*max_len, curr_len);
            curr_len = 2;
        }
        else
        {
            *max_len = MAX(*max_len, curr_len);
            curr_len = 0;
        }

        prev_prev_num = prev_num;
        prev_num = curr_num;
    }
    *max_len = MAX(*max_len, curr_len);

    char c;
    rc = fscanf(f, "%c", &c);
    
    return OKAY;
}
