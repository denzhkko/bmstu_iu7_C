#include "check_array_io.h"

#define FILES_DIR "unit_tests/files/"

// count_integer_in_file func

// NEGATIVE TESTS

#define NEG_CIIF(filename, ERROR_CODE)              \
int rc;                                             \
size_t int_count = 0;                               \
rc = count_integers_in_file(filename, &int_count);  \
ck_assert_int_eq(ERROR_CODE, rc);

START_TEST(neg_ciif_incorrect)
{
    NEG_CIIF(FILES_DIR "neg_ciif_incorrect.txt", WRONG_SYMBOL_FOUND);
}
END_TEST

// POSITIVE TESTS

#define POS_CIIF(FILENAME, INT_COUNT)               \
int rc;                                             \
size_t int_count;                                   \
rc = count_integers_in_file(FILENAME, &int_count);  \
ck_assert_int_eq(OKAY, rc);                         \
ck_assert(int_count == INT_COUNT);

START_TEST(pos_ciif_0_num)
{
    POS_CIIF(FILES_DIR "pos_ciif_0_num.txt", 0);
}
END_TEST

START_TEST(pos_ciif_1_num)
{
    POS_CIIF(FILES_DIR "pos_ciif_1_num.txt", 1);
}
END_TEST

START_TEST(pos_ciif_10_num)
{
    POS_CIIF(FILES_DIR "pos_ciif_10_num.txt", 10);
}
END_TEST

Suite *suite_create_count_integers_in_file(void)
{
    Suite *s;
    TCase *tcase_pos;
    TCase *tcase_neg;

    s = suite_create("count_integers_in_file");

    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_neg, neg_ciif_incorrect);

    suite_add_tcase(s, tcase_neg);
    
    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pos_ciif_0_num);
    tcase_add_test(tcase_pos, pos_ciif_1_num);
    tcase_add_test(tcase_pos, pos_ciif_10_num);

    suite_add_tcase(s, tcase_pos);

    return s;
}

// Func file_to_array

// Positive tests

#define POS_FTA(FILENAME, ARR_LEN)                                  \
darray_int_t *darr;                                                 \
darray_int_init(&darr, ARR_LEN);                                    \
int rc = file_to_array(FILENAME, darr);                             \
ck_assert_int_eq(rc, OKAY);                                         \
for (size_t i = 0; i < ARR_LEN; ++i)                                   \
    ck_assert_int_eq(darray_int_get(darr, i), *(temp_array + i));   \
darray_int_free(darr);

START_TEST(neg_fta_0_num)
{
    darray_int_t *arr;
    darray_int_init(&arr, 0);

    int rc = file_to_array(FILES_DIR "pos_fta_0_num.txt", arr);
    
    darray_int_free(arr);
    ck_assert_int_eq(rc, OKAY);
}

START_TEST(pos_fta_1_num)
{
    int temp_array[] = {1};
    POS_FTA(FILES_DIR "pos_fta_1_num.txt", 1);
}

START_TEST(pos_fta_10_num)
{
    int temp_array[] = {1, 3, 4, 2, 3, 4, 1, 2, 3, 4};
    POS_FTA(FILES_DIR "pos_fta_10_num.txt", 10);
}

#undef POS_FTA

Suite *suite_create_file_to_array(void)
{
    
    Suite *s;
    TCase *tcase_pos;
    TCase *tcase_neg;

    s = suite_create("file_to_array");

    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_neg, neg_fta_0_num);

    suite_add_tcase(s, tcase_neg);

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pos_fta_1_num);
    tcase_add_test(tcase_pos, pos_fta_10_num);

    suite_add_tcase(s, tcase_pos);

    return s;
}
