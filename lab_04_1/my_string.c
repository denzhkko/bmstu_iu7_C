#include <stdio.h>
#include "my_string.h"

char *my_strpbrk(const char *s, const char *accept)
{
    for (char *ps = (char *) s; *ps; ++ps)
        for (char *pa = (char *) accept; *pa; ++pa)
            if (*ps == *pa)
                return ps;

    return NULL;
}
