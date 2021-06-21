#include "check_strio.h"

#define SST_NEG(FILENAME, RC) \
size_t value; \
FILE *f = fopen(FILENAME, "r"); \
ck_assert_ptr_ne(NULL, f); \
int rc = scanf_size_t(f, &value); \
ck_assert_int_eq(RC, rc); \
fclose(f);

START_TEST(sst_neg_empty)
{
    SST_NEG("unit_tests/files/strio/sst_neg_empty.txt", EOF);
}

START_TEST(sst_neg_negative_num)
{
    SST_NEG("unit_tests/files/strio/sst_neg_negative.txt", 0);
}

#define SST_POS(FILENAME, RC, VALUE) \
size_t value; \
FILE *f = fopen(FILENAME, "r"); \
ck_assert_ptr_ne(NULL, f); \
int rc = scanf_size_t(f, &value); \
ck_assert_int_eq(RC, rc); \
ck_assert(VALUE == value); \
fclose(f);

START_TEST(sst_pos)
{
    SST_POS("unit_tests/files/strio/sst_pos.txt", 1, 12345678);
}

Suite *suite_scanf_size_t(void)
{
    Suite *suite;

    TCase *tcase_neg;
    TCase *tcase_pos;

    suite = suite_create("scanf_size_t");

    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_neg, sst_neg_empty);
    tcase_add_test(tcase_neg, sst_neg_negative_num);

    suite_add_tcase(suite, tcase_neg);

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, sst_pos);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}
