#include "../inc/mymath.h"

unsigned upow(unsigned num, unsigned power)
{
    unsigned res = 1;

    for (unsigned i = 0; i < power; ++i)
        res *= num;

    LOG_TRACE("%u ^ %u == %u", num, power, res);
    return res;
}
