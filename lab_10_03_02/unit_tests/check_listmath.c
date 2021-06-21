#include "check_listmath.h"

#define NTL(arr, NUM) \
struct num_node *head = num_to_listnum(NUM), *node; \
ck_assert_ptr_nonnull(head); \
unsigned i =  0; \
LIST_FOR_EACH_ENTRY(node, &head->list, list, struct num_node) \
{ \
    ck_assert(i < sizeof(arr) / sizeof(arr[0])); \
    ck_assert_uint_eq(arr[i], node->power); \
    ++i; \
} \
ck_assert_uint_eq(i, sizeof(arr) / sizeof(arr[0])); \
listnum_free(head);

START_TEST(ntl_pos_1)
{
    unsigned arr[] = {0};
    NTL(arr, 1);
}
END_TEST

START_TEST(ntl_pos_3)
{
    unsigned arr[] = {0, 1};
    NTL(arr, 3);
}
END_TEST

START_TEST(ntl_pos_50)
{
    unsigned arr[] = {1, 0, 2};
    NTL(arr, 50);
}
END_TEST

START_TEST(ntl_pos_1980)
{
    unsigned arr[] = {2, 2, 1, 0, 1};
    NTL(arr, 1980);
}
END_TEST

Suite *suite_num_to_listnum(void)
{
    Suite *suite;

    TCase *tcase_pos;

    suite = suite_create("num_to_listnum");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, ntl_pos_1);
    tcase_add_test(tcase_pos, ntl_pos_3);
    tcase_add_test(tcase_pos, ntl_pos_50);
    tcase_add_test(tcase_pos, ntl_pos_1980);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

#define LTN(NUM) \
struct num_node *head = num_to_listnum(NUM); \
ck_assert_ptr_nonnull(head); \
unsigned res = listnum_to_num(head); \
ck_assert_uint_eq(NUM, res); \
listnum_free(head);

START_TEST(ltn_pos_1)
{
    LTN(1);
}
END_TEST

START_TEST(ltn_pos_3)
{
    LTN(3);
}
END_TEST

START_TEST(ltn_pos_50)
{
    LTN(50);
}
END_TEST

START_TEST(ltn_pos_1980)
{
    LTN(1980);
}
END_TEST

START_TEST(ltn_pos_11341)
{
    LTN(11341);
}

Suite *suite_listnum_to_num(void)
{
    Suite *suite;

    TCase *tcase_pos;

    suite = suite_create("listnum_to_num");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, ltn_pos_1);
    tcase_add_test(tcase_pos, ltn_pos_3);
    tcase_add_test(tcase_pos, ltn_pos_50);
    tcase_add_test(tcase_pos, ltn_pos_1980);
    tcase_add_test(tcase_pos, ltn_pos_11341);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

#define LM(NUM_1, NUM_2, COMP) \
struct num_node *f_head = num_to_listnum(NUM_1); \
ck_assert_ptr_nonnull(f_head); \
struct num_node *s_head = num_to_listnum(NUM_2); \
ck_assert_ptr_nonnull(s_head); \
struct num_node *comp = listnum_mul(f_head, s_head); \
ck_assert_ptr_nonnull(comp); \
ck_assert_uint_eq(COMP, listnum_to_num(comp)); \
listnum_free(comp); \
listnum_free(s_head); \
listnum_free(f_head);

START_TEST(lm_pos_1_1)
{
    LM(1, 1, 1);
}

START_TEST(lm_pos_1_2)
{
    LM(1, 2, 2);
}

START_TEST(lm_pos_10_3)
{
    LM(10, 3, 30);
}

Suite *suite_listnum_mul(void)
{
    Suite *suite;

    TCase *tcase_pos;

    suite = suite_create("listnum_mul");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, lm_pos_1_1);
    tcase_add_test(tcase_pos, lm_pos_1_2);
    tcase_add_test(tcase_pos, lm_pos_10_3);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}


#define LC(NUM) \
struct num_node *src = num_to_listnum(NUM); \
ck_assert_ptr_nonnull(src); \
unsigned src_num = listnum_to_num(src); \
ck_assert_uint_eq(NUM, src_num); \
struct num_node *dst = listnum_copy(src); \
ck_assert_ptr_nonnull(dst); \
unsigned dst_num = listnum_to_num(dst); \
ck_assert_uint_eq(NUM, dst_num); \
listnum_free(dst); \
listnum_free(src);

START_TEST(lc_pos_1)
{
    LC(1);
}

START_TEST(lc_pos_2)
{
    LC(2);
}

START_TEST(lc_pos_1861)
{
    LC(1861);
}

Suite *suite_listnum_copy(void)
{
    Suite *suite;

    TCase *tcase_pos;

    suite = suite_create("listnum_copy");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, lc_pos_1);
    tcase_add_test(tcase_pos, lc_pos_2);
    tcase_add_test(tcase_pos, lc_pos_1861);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

#define LS(NUM) \
struct num_node *num_head = num_to_listnum(NUM); \
ck_assert_ptr_nonnull(num_head); \
struct num_node *sqr_head = listnum_sqr(num_head); \
ck_assert_ptr_nonnull(sqr_head); \
const unsigned sqr = listnum_to_num(sqr_head); \
ck_assert_uint_eq(NUM * NUM, sqr); \
listnum_free(sqr_head); \
listnum_free(num_head);

START_TEST(ls_pos_1)
{
    LS(1);
}
END_TEST

START_TEST(ls_pos_2)
{
    LS(2);
}
END_TEST

START_TEST(ls_pos_11)
{
    LS(11);
}
END_TEST

Suite *suite_listnum_sqr(void)
{
    Suite *suite;

    TCase *tcase_pos;

    suite = suite_create("listnum_sqr");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, ls_pos_1);
    tcase_add_test(tcase_pos, ls_pos_2);
    tcase_add_test(tcase_pos, ls_pos_11);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

#define LD_NEG(NUM_1, NUM_2) \
struct num_node *f_head = num_to_listnum(NUM_1); \
ck_assert_ptr_nonnull(f_head); \
struct num_node *s_head = num_to_listnum(NUM_2); \
ck_assert_ptr_nonnull(s_head); \
struct num_node *div_head; \
int rc = listnum_div(f_head, s_head, &div_head); \
ck_assert_int_eq(ERR_ZERO_GOT, rc); \
listnum_free(s_head); \
listnum_free(f_head);

START_TEST(ld_neg_5_6)
{
    LD_NEG(5, 6);
}

START_TEST(ld_neg_1_60)
{
    LD_NEG(1, 60);
}

#define LD_POS(NUM_1, NUM_2) \
struct num_node *f_head = num_to_listnum(NUM_1); \
ck_assert_ptr_nonnull(f_head); \
struct num_node *s_head = num_to_listnum(NUM_2); \
ck_assert_ptr_nonnull(s_head); \
struct num_node *div_head; \
int rc = listnum_div(f_head, s_head, &div_head); \
ck_assert_int_eq(OKAY, rc); \
unsigned div = listnum_to_num(div_head); \
ck_assert_uint_eq(NUM_1 / NUM_2, div); \
listnum_free(div_head); \
listnum_free(s_head); \
listnum_free(f_head);

START_TEST(ld_pos_6_3)
{
    LD_POS(6, 3);
}

START_TEST(ld_pos_5_3)
{
    LD_POS(5, 3);
}

Suite *suite_listnum_div(void)
{
    Suite *suite;

    TCase *tcase_pos;
    TCase *tcase_neg;

    suite = suite_create("listnum_div");

    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_neg, ld_neg_5_6);
    tcase_add_test(tcase_neg, ld_neg_1_60);

    suite_add_tcase(suite, tcase_neg);

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, ld_pos_5_3);
    tcase_add_test(tcase_pos, ld_pos_6_3);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}
