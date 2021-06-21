#include "../inc/prime_num.h"

bool is_num_prime(size_t num)
{
    if (num <= 1)
        return false;

    for (size_t i = 2; i < num / 2 + 1; ++i)
        if (0 == num % i)
            return false;

    return true;
}

size_t next_prime_num(size_t num)
{
    size_t next = num + 1;

    while (!is_num_prime((next)))
        ++next;

    return next;
}
