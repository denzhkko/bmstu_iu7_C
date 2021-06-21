#ifndef _LAB_07_ARRAY_H_

#define _LAB_07_ARRAY_H_

#include <stdlib.h>
#include <sys/types.h> 

#include "macrologger.h"

#include "darray.h"

#define SWAP(a, b, size)            \
{                                   \
    size_t __size = (size);         \
    char *__a = (a), *__b = (b);    \
    do                              \
        {                           \
            char __tmp = *__a;      \
            *__a++ = *__b;          \
            *__b++ = __tmp;         \
        } while (--__size > 0);     \
}

#define CMP_GREATER                     1
#define CMP_LESS                        -1
#define CMP_EQUAL                       0

#define OKAY                            0
#define UNABLE_T0_CREATE_F_ARRAY        1
#define INCORRECT_SRC_PTR               2
#define ZERO_F_ARRAY_LEN                3

/**
 * @brief Filter array
 *
 * The array contains elements that are greater than the sum of the numbers
 * behind them
 *
 * @return OKAY if syccess;
 * UNABLE_T0_CREATE_F_ARRAY if unable to get memory for filtered array;
 * INCORRECT_SRC_PTR if incorrect input data;
 * ZERO_ARRAY_LEN if zero array destination len;
 */
int key(int *pb_src, int *pe_src, int **pb_dst, int **pe_dst);

/**
 * @brief Compare two integer
 *
 * @return 0 if number equal;
 */
int compare_int(const void *v_num1, const void *v_num2);

/**
 * @brief Selection sort
 */
void mysort(void *ptr, size_t count, size_t size,
int (*comp)(const void *, const void *));

#endif // _LAB_07_ARRAY_H_
