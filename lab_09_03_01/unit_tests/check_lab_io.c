#include "check_lab_io.h"

#define NEG_GTN(FILENAME, RC) \
int rc; \
FILE *f = fopen(FILENAME, "r"); \
ck_assert_ptr_ne(NULL, f); \
size_t title_num; \
rc = read_size_t(f, &title_num); \
ck_assert_int_eq(RC, rc); \
rc = fclose(f); \
ck_assert_int_ne(EOF, rc);

START_TEST(neg_gtn_empty)
{
    NEG_GTN("unit_tests/files/neg_gtn_empty.txt", EOF);
}

START_TEST(neg_gtn_no_num)
{
    NEG_GTN("unit_tests/files/neg_gtn_no_num.txt", NUM_GET_FAILED);
}

START_TEST(neg_gtn_neg_num)
{
    NEG_GTN("unit_tests/files/neg_gtn_neg_num.txt", NEGATIVE_NUM);
}

START_TEST(neg_gtn_incorrect_file)
{
    NEG_GTN("unit_tests/files/neg_gtn_incorrect_file.txt",
    INCORRECT_FILE);
}

#define POS_GTN(FILENAME, TITLE_NUM) \
int rc; \
FILE *f = fopen(FILENAME, "r"); \
ck_assert_ptr_ne(NULL, f); \
size_t title_num; \
rc = read_size_t(f, &title_num); \
ck_assert_int_eq(OKAY, rc); \
ck_assert_int_eq((int) TITLE_NUM, (int) title_num); \
rc = fclose(f); \
ck_assert_int_ne(EOF, rc);

START_TEST(pos_gtn)
{
    POS_GTN("unit_tests/files/pos_gtn.txt", 123);
}
END_TEST

Suite *suite_create_get_title_num(void)
{
    Suite *suite;
    TCase *tcase_pos;
    TCase *tcase_neg;

    suite = suite_create("get_title_num");

    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_neg, neg_gtn_empty);
    tcase_add_test(tcase_neg, neg_gtn_no_num);
    tcase_add_test(tcase_neg, neg_gtn_neg_num);
    tcase_add_test(tcase_neg, neg_gtn_incorrect_file);

    suite_add_tcase(suite, tcase_neg);

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pos_gtn);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

#define NEG_RPL(FILENAME, RC) \
int rc; \
FILE *f = fopen(FILENAME, "r"); \
ck_assert_ptr_ne(NULL, f); \
product_t product; product.name = NULL; \
char *buffer = NULL; size_t buffer_len = 0; \
rc = read_product(f, &product, &buffer, &buffer_len); \
free(buffer); \
ck_assert_int_eq(RC, rc); \
rc = fclose(f); \
ck_assert_int_ne(EOF, rc);

START_TEST(neg_rlp_empty)
{
    NEG_RPL("unit_tests/files/neg_rpl_empty.txt", EOF);
}
END_TEST

START_TEST(neg_rlp_eof_after_name)
{
    NEG_RPL("unit_tests/files/neg_rpl_eof_after_name.txt",
    INCORRECT_FILE);
}
END_TEST

#define POS_RPL(FILENAME, NAME, PRICE) \
int rc; \
FILE *f = fopen(FILENAME, "r"); \
ck_assert_ptr_ne(NULL, f); \
product_t product; product.name = NULL;\
char *buffer = NULL; size_t buffer_len = 0; \
rc = read_product(f, &product, &buffer, &buffer_len); \
free(buffer); \
ck_assert_int_eq(OKAY, rc); \
ck_assert_str_eq(product.name, NAME); \
ck_assert_uint_eq(product.price, PRICE); \
free(product.name); \
rc = fclose(f); \
ck_assert_int_ne(EOF, rc);

START_TEST(pos_rpl)
{
    POS_RPL("unit_tests/files/pos_rpl.txt", "cake", 100);
}
END_TEST

Suite *suite_create_read_product_line(void)
{
    Suite *suite;
    TCase *tcase_pos;
    TCase *tcase_neg;

    suite = suite_create("read_product_line");

    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_neg, neg_rlp_empty);
    tcase_add_test(tcase_neg, neg_rlp_eof_after_name);

    suite_add_tcase(suite, tcase_neg);

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pos_rpl);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}
