#include "check_product.h"

#define PRODUCT_INIT(VARNAME, NAME, PRICE)          \
product_t VARNAME;                                  \
VARNAME.price = 100;                                \
VARNAME.name = "Some word";

#define POS_VAP(PRIMARY_LEN) \
int rc; \
vector_t *vector = vector_allocate(PRIMARY_LEN, sizeof(product_t)); \
ck_assert_ptr_ne(NULL, vector); \
PRODUCT_INIT(product, "Some word", 100); \
rc = vector_append_product(vector, product); \
ck_assert_int_eq(OKAY, rc); \
size_t len = vector_get_length(vector); \
product_t vector_product = vector_get_product_at(vector, len - 1); \
ck_assert_str_eq(product.name, vector_product.name); \
ck_assert_uint_eq(product.price, vector_product.price); \
ck_assert(PRIMARY_LEN + 1 == len); \
vector_free(vector);

START_TEST(pos_vap_0_len)
{
    POS_VAP(0);
}
END_TEST

START_TEST(pos_vap_10_len)
{
    POS_VAP(10);
}
END_TEST

Suite *suite_create_vector_append_product(void)
{
    Suite *suite;
    TCase *tcase_pos;

    suite = suite_create("vector_append_product");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pos_vap_0_len);
    tcase_add_test(tcase_pos, pos_vap_10_len);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}
