#include "check_lab_07_array.h"

int copy_darray(int **darray, const int *const array, const size_t len)
{
    *darray = (int *) malloc(len * sizeof(int));
    
    if (NULL == *darray)
    {
        LOG_ERROR("%s", "malloc failed");
        return MALLOC_FAULED;
    }

    for (size_t i = 0; i < len; ++i)
        *(*darray + i) = array[i];

    return OKAY;
}

int cmp_darray(int *darray, int *array, size_t len)
{
    for (size_t i = 0; i < len; ++i)
        if (*(darray + i) != *(array + i))
        {
            LOG_ERROR("i == %zu; darr_i == %d; arr_i == %d", i, *(darray + i),
            *(array + i));
            return DIFFERENT_ARRAYS;
        }

    return OKAY;
}

// Func key

// Negative tests
#define LEN_SRC 3
#define LEN_DST 3
START_TEST(neg_k_zero_len_filtered_array)
{
    int arr_src[] = {1, 2, 3};
    int rc;
    int *darr_src;

    rc = copy_darray(&darr_src, arr_src, LEN_SRC);
    ck_assert_int_eq(rc, OKAY);

    size_t dst_arr_len = key_count_suit(darr_src, darr_src + LEN_SRC);
    ck_assert_uint_eq(0, (unsigned) dst_arr_len);
    free(darr_src);
}
END_TEST
#undef LEN_SRC
#undef LEN_DST

// Positive tests

#define POS_K(LEN_SRC, LEN_DST)                                     \
int rc;                                                             \
int *darr_src, *darr_dst, *darr_dst_end;                            \
rc = copy_darray(&darr_src, arr_src, LEN_SRC);                      \
ck_assert_int_eq(rc, OKAY);                                         \
    size_t dst_arr_len = key_count_suit(darr_src, darr_src + LEN_SRC); \
    darr_dst = (int *) malloc(dst_arr_len * sizeof(int)); \
    ck_assert_ptr_nonnull(darr_dst); \
    darr_dst_end = darr_dst + dst_arr_len; \
rc = key(darr_src, darr_src + LEN_SRC, &darr_dst, &darr_dst_end);   \
ck_assert_int_eq(rc, OKAY);                                         \
ck_assert_int_eq(LEN_DST, darr_dst_end - darr_dst);                 \
rc = cmp_darray(darr_dst, arr_dst, LEN_DST);                        \
ck_assert_int_eq(rc, OKAY);                                         \
free(darr_dst);

START_TEST(pos_k_one_len_filtered_array)
{
    int arr_src[] = {3, 2, 1}, arr_dst[] = {2};
    POS_K(3, 1);
}
END_TEST

START_TEST(pos_k_all_len_filtered_array)
{
    int arr_src[] = {10, 4, 2, 1}, arr_dst[] = {10, 4, 2};
    POS_K(4, 3);
}
END_TEST

#undef POS_K

Suite *suite_create_key(void)
{
    Suite *s;
    TCase *tcase_neg;
    TCase *tcase_pos;

    s = suite_create("key");

    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_neg, neg_k_zero_len_filtered_array);

    suite_add_tcase(s, tcase_neg);

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pos_k_one_len_filtered_array);
    tcase_add_test(tcase_pos, pos_k_all_len_filtered_array);

    suite_add_tcase(s, tcase_pos);

    return s;
}

// Func compare int

// Positive tests
#define POS_CMP(NUM1, NUM2, RC)         \
int num1 = NUM1, num2 = NUM2;           \
int rc = compare_int(&num1, &num2);     \
ck_assert_int_eq(rc, RC);

START_TEST(pos_ci_gt)
{
    POS_CMP(10, 0, CMP_GREATER);
}
END_TEST

START_TEST(pos_ci_gt_with_neg)
{
    POS_CMP(0, -10, CMP_GREATER);
}
END_TEST

START_TEST(pos_ci_gt_neg)
{
    POS_CMP(-5, -10, CMP_GREATER);
}
END_TEST

START_TEST(pos_ci_eq)
{
    POS_CMP(5, 5, CMP_EQUAL);
}
END_TEST

START_TEST(pos_ci_eq_neg)
{
    POS_CMP(-5, -5, CMP_EQUAL);
}
END_TEST

START_TEST(pos_ci_lt)
{
    POS_CMP(10, 15, CMP_LESS);
}
END_TEST

START_TEST(pos_ci_lt_with_neg)
{
    POS_CMP(-10, 10, CMP_LESS);
}
END_TEST

START_TEST(pos_ci_lt_neg)
{
    POS_CMP(-10, -5, CMP_LESS);
}
END_TEST

#undef POS_CMP

Suite *suite_create_compare_int(void)
{
    Suite *s;
    TCase *tcase_pos;

    s = suite_create("compare_int");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pos_ci_gt);
    tcase_add_test(tcase_pos, pos_ci_gt_with_neg);
    tcase_add_test(tcase_pos, pos_ci_gt_neg);
    tcase_add_test(tcase_pos, pos_ci_eq);
    tcase_add_test(tcase_pos, pos_ci_eq_neg);
    tcase_add_test(tcase_pos, pos_ci_lt);
    tcase_add_test(tcase_pos, pos_ci_lt_with_neg);
    tcase_add_test(tcase_pos, pos_ci_lt_neg);

    suite_add_tcase(s, tcase_pos);

    return s;
}

// Func mysort

// Positive tests

#define POS_MS(LEN)                             \
int rc;                                         \
int *darr;                                      \
rc = copy_darray(&darr, arr_src, LEN);          \
ck_assert_int_eq(rc, OKAY);                     \
mysort(darr, LEN, sizeof(int), *compare_int);   \
rc = cmp_darray(darr, arr_dst, LEN);            \
ck_assert_int_eq(rc, OKAY);                     \
free(darr);

#define LEN 1
START_TEST(pos_ms_1)
{
    int arr_src[] = {1}, arr_dst[] = {1};
    POS_MS(LEN);
}
END_TEST
#undef LEN

#define LEN 3
START_TEST(pos_ms_3)
{
    int arr_src[] = {2, 3, 1}, arr_dst[] = {1, 2, 3};
    POS_MS(LEN);
}
END_TEST
#undef LEN

#define LEN 3
START_TEST(pos_ms_3_sorted)
{
    int arr_src[] = {1, 2, 3}, arr_dst[] = {1, 2, 3};
    POS_MS(LEN);
}
END_TEST
#undef LEN

#define LEN 10
START_TEST(pos_ms_10)
{
    int arr_src[] = {4, -1, -100, 1314, 0, 3, 4, -123, 1, 0},
    arr_dst[] = {-123, -100, -1, 0, 0, 1, 3, 4, 4, 1314};
    POS_MS(LEN);
}
END_TEST
#undef LEN

#undef POS_MS

Suite *suite_create_mysort(void)
{
    Suite *s;
    TCase *tcase_pos;

    s = suite_create("mysort");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pos_ms_1);
    tcase_add_test(tcase_pos, pos_ms_3);
    tcase_add_test(tcase_pos, pos_ms_3_sorted);
    tcase_add_test(tcase_pos, pos_ms_10);

    suite_add_tcase(s, tcase_pos);

    return s;
}
