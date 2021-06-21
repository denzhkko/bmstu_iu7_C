#include "../inc/num.h"

unsigned get_num_len(int num)
{
    num = abs(num);

    unsigned num_len = 0;

    do
    {
        num /= 10;
        ++num_len;
    }
    while (num);

    return num_len;
}

int power(int num, unsigned power)
{
    int res = 1;
    for (unsigned i = 0; i < power; ++i)
    {
        res *= num;
    }

    return res;
}
