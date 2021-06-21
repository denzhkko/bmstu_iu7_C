#include "../inc/lab_07_array.h"

int key(int *pb_src, int *pe_src, int **pb_dst, int **pe_dst)
{
    if (NULL == pb_src || NULL == pe_src || pb_src >= pe_src)
    {
        LOG_ERROR("Incorrect input pts: pb_src = %p; pe_src = %p",
        (const void *) pb_src, (const void *) pe_src);

        return INCORRECT_SRC_PTR;
    }

    size_t dst_len = 0;
    int sum;

    sum = *(pe_src - 1);

    for (int *p = (int *) pe_src - 2; p >= pb_src; --p)
    {
        if (*p > sum)
            ++dst_len;

        sum += *p;
    }

    LOG_INFO("Filtered array len: %zu", dst_len);

    if (0 == dst_len)
    {
        LOG_ERROR("%s", "0 dest array len");
        return ZERO_F_ARRAY_LEN;
    }

    *pb_dst = (int *) malloc(dst_len * sizeof(int));
    
    if (NULL == *pb_dst)
    {
        LOG_ERROR("malloc failed for %zu ints", dst_len);
        return UNABLE_T0_CREATE_F_ARRAY;
    }

    *pe_dst = *pb_dst + dst_len;
    
    sum = *(pe_src - 1);
    for (int *p_src = (int *) pe_src - 2, *p_dst = *pe_dst - 1;
    p_src >= pb_src; --p_src)
    {
        if (*p_src > sum)
        {
            *p_dst = *p_src;
            --p_dst;
        }

        sum += *p_src;
    }

    free((int *) pb_src);

    return OKAY;
}

int compare_int(const void *v_num1, const void *v_num2)
{
    int num1 = *((const int *) v_num1);
    int num2 = *((const int *) v_num2);

    return (num1 > num2) ? CMP_GREATER : (num1 < num2) ? CMP_LESS : CMP_EQUAL;
}

void mysort(void *ptr, size_t count, size_t size,
int (*comp)(const void *, const void *))
{
    if (0 == count)
        return;

    for (size_t i = count - 1; i >= 1; --i)
    {
        size_t max_v_i = 0;
        for (size_t j = 1; j <= i; ++j)
        {
            void *p_cur_elem = (char *) ptr + j * size;
            void *p_max_elem = (char *) ptr + max_v_i * size;

            if (comp(p_cur_elem, p_max_elem) > 0)
                max_v_i = j;
        }
        SWAP((char *) ptr + max_v_i * size, (char *) ptr + i * size, size);
    }
}
