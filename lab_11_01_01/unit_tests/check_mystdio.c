#include "check_mystdio.h"

#define DEF_FORMAT                      "123"

#define MS(BUFF_LEN, ...) \
int rc, my_rc; \
char *buffer = calloc(BUFF_LEN, sizeof(char)); \
ck_assert_ptr_nonnull(buffer); \
char *my_buffer = calloc(BUFF_LEN, sizeof(char)); \
ck_assert_ptr_nonnull(my_buffer); \
size_t buff_len = BUFF_LEN; \
rc = snprintf(buffer, buff_len, __VA_ARGS__); \
my_rc = my_snprintf(my_buffer, BUFF_LEN, __VA_ARGS__); \
ck_assert_int_eq(rc, my_rc); \
ck_assert_str_eq(buffer, my_buffer); \
free(my_buffer); \
free(buffer);

START_TEST(ms_neg_empty)
{
    #pragma GCC diagnostic ignored "-Wformat-zero-length"
    MS(5, "");
}
END_TEST

#define BUFF_LEN                        0
#define FORMAT                          DEF_FORMAT
START_TEST(ms_neg_zero_len)
{
    int rc, my_rc;
    char *buffer = "literal";
    char *my_buffer = "literal";
    size_t buff_len = BUFF_LEN;
    rc = snprintf(buffer, buff_len, FORMAT);
    ck_assert_int_ne(rc, rc + 1);
    my_rc = my_snprintf(my_buffer, BUFF_LEN, FORMAT);
    ck_assert_int_eq(rc, my_rc);
}
END_TEST
#undef FORMAT
#undef BUFF_LEN

START_TEST(ms_pos_per_cent)
{
    MS(4, "12%%");
}
END_TEST

START_TEST(ms_pos_just_str)
{
    MS(5, DEF_FORMAT);
}
END_TEST

START_TEST(ms_pos_format_len_eq_buffer_len)
{
    MS(4, DEF_FORMAT);
}
END_TEST

START_TEST(ms_pos_format_len_gr_buffer_len)
{
    MS(3, DEF_FORMAT);
}
END_TEST

Suite *suite_my_snprintf(void)
{
    Suite *suite;

    TCase *tcase_neg;
    TCase *tcase_pos;

    suite = suite_create("my_snprintf");


    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_neg, ms_neg_empty);
    tcase_add_test(tcase_neg, ms_neg_zero_len);

    suite_add_tcase(suite, tcase_neg);

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, ms_pos_per_cent);
    tcase_add_test(tcase_pos, ms_pos_just_str);
    tcase_add_test(tcase_pos, ms_pos_format_len_eq_buffer_len);
    tcase_add_test(tcase_pos, ms_pos_format_len_gr_buffer_len);
    tcase_add_test(tcase_pos, ms_pos_format_len_gr_buffer_len);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

START_TEST(ms_pos_char)
{
    MS(3, "%c", 'a');
}
END_TEST

START_TEST(ms_pos_char_two)
{
    MS(3, "%c%c", 'a', 'b');
}
END_TEST

START_TEST(ms_pos_char_two_more)
{
    MS(6, "%c+1=%c", 'a', 'b');
}
END_TEST

START_TEST(ms_pos_char_two_more_buffer_not_enough)
{
    MS(2, "%c+1=%c", 'a', 'b');
}
END_TEST

Suite *suite_my_snprintf_char(void)
{
    Suite *suite;

    TCase *tcase_pos;

    suite = suite_create("my_snprintf with char");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, ms_pos_char);
    tcase_add_test(tcase_pos, ms_pos_char_two);
    tcase_add_test(tcase_pos, ms_pos_char_two_more);
    tcase_add_test(tcase_pos, ms_pos_char_two_more_buffer_not_enough);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

START_TEST(ms_pos_int)
{
    MS(3, "%d", 1);
}
END_TEST

START_TEST(ms_pos_int_big)
{
    MS(6, "%d", 15234);
}
END_TEST

START_TEST(ms_pos_int_bigger)
{
    MS(3, "%d", 15234);
}
END_TEST

START_TEST(ms_pos_int_two)
{
    MS(3, "%d%d", 1, 2);
}
END_TEST

START_TEST(ms_pos_int_two_more)
{
    MS(6, "%d+1=%d", 1, 2);
}
END_TEST

START_TEST(ms_pos_int_zero)
{
    MS(3, "%d", 0);
}
END_TEST

START_TEST(ms_pos_int_zero_plus_num)
{
    MS(10, "%d + %d", 0, 15);
}
END_TEST

START_TEST(ms_pos_int_max)
{
    MS(30, "%d", INT_MAX);
}
END_TEST

START_TEST(ms_pos_int_negative)
{
    MS(30, "%d", -123);
}
END_TEST

START_TEST(ms_pos_int_min)
{
    MS(30, "%d", INT_MIN);
}
END_TEST

START_TEST(ms_pos_int_buffer_not_enough)
{
    MS(2, "%d + %d = %d", 1, 2, 3);
}
END_TEST

START_TEST(ms_pos_int_minus_2147483640)
{
    MS(100, "%d", 2147483640);
}
END_TEST

Suite *suite_my_snprintf_int(void)
{
    Suite *suite;

    TCase *tcase_pos;

    suite = suite_create("my_snprintf with int");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, ms_pos_int);
    tcase_add_test(tcase_pos, ms_pos_int_big);
    tcase_add_test(tcase_pos, ms_pos_int_bigger);
    tcase_add_test(tcase_pos, ms_pos_int_two);
    tcase_add_test(tcase_pos, ms_pos_int_two_more);
    tcase_add_test(tcase_pos, ms_pos_int_zero);
    tcase_add_test(tcase_pos, ms_pos_int_zero_plus_num);
    tcase_add_test(tcase_pos, ms_pos_int_max);
    tcase_add_test(tcase_pos, ms_pos_int_negative);
    tcase_add_test(tcase_pos, ms_pos_int_min);
    tcase_add_test(tcase_pos, ms_pos_int_buffer_not_enough);
    tcase_add_test(tcase_pos, ms_pos_int_minus_2147483640);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

START_TEST(ms_neg_short_incorrect)
{
    #pragma GCC diagnostic ignored "-Wformat"
    #pragma GCC diagnostic ignored "-Wformat-extra-args"
    MS(3, "%h", (short) 1);
}
END_TEST

START_TEST(ms_pos_short)
{
    MS(3, "%hd", (short) 1);
}
END_TEST

START_TEST(ms_pos_short_big)
{
    MS(6, "%hd", (short) 15234);
}
END_TEST

START_TEST(ms_pos_short_bigger)
{
    MS(3, "%hd", (short) 15234);
}
END_TEST

START_TEST(ms_pos_short_two)
{
    MS(3, "%hd%hd", (short) 1, (short) 2);
}
END_TEST

START_TEST(ms_pos_short_two_more)
{
    MS(6, "%hd+1=%hd", (short) 1, (short) 2);
}
END_TEST

START_TEST(ms_pos_short_zero)
{
    MS(3, "%hd", (short) 0);
}
END_TEST

START_TEST(ms_pos_short_zero_plus_num)
{
    MS(10, "%hd + %hd", (short) 0, (short) 15);
}
END_TEST

START_TEST(ms_pos_short_max)
{
    MS(30, "%hd", (short) SHRT_MAX);
}
END_TEST

START_TEST(ms_pos_short_negative)
{
    MS(30, "%hd", (short) -123);
}
END_TEST

START_TEST(ms_pos_short_min)
{
    MS(30, "%hd", (short) SHRT_MIN);
}
END_TEST

START_TEST(ms_pos_short_buffer_not_enough)
{
    MS(2, "%hd + %hd = %hd", (short) 1, (short) 2, (short) 3);
}
END_TEST

Suite *suite_my_snprintf_short(void)
{
    Suite *suite;

    TCase *tcase_neg;
    TCase *tcase_pos;

    suite = suite_create("my_snprintf with short");

    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_neg, ms_neg_short_incorrect);

    suite_add_tcase(suite, tcase_neg);

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, ms_pos_short);
    tcase_add_test(tcase_pos, ms_pos_short_big);
    tcase_add_test(tcase_pos, ms_pos_short_bigger);
    tcase_add_test(tcase_pos, ms_pos_short_two);
    tcase_add_test(tcase_pos, ms_pos_short_two_more);
    tcase_add_test(tcase_pos, ms_pos_short_zero);
    tcase_add_test(tcase_pos, ms_pos_short_zero_plus_num);
    tcase_add_test(tcase_pos, ms_pos_short_max);
    tcase_add_test(tcase_pos, ms_pos_short_negative);
    tcase_add_test(tcase_pos, ms_pos_short_min);
    tcase_add_test(tcase_pos, ms_pos_short_buffer_not_enough);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

START_TEST(ms_pos_string_default)
{
    MS(10, "%s", "some str");
}
END_TEST

START_TEST(ms_pos_string_emtpy)
{
    MS(10, "%s", "");
}
END_TEST

START_TEST(ms_pos_string_two)
{
    MS(10, "%s%s", "some ", "str");
}
END_TEST

START_TEST(ms_pos_string_two_with_another_symbols)
{
    MS(20, "%s :( %s", "some ", "str");
}
END_TEST

START_TEST(ms_pos_string_not_enough)
{
    MS(10, "%s :( %s", "some ", "str");
}
END_TEST

Suite *suite_my_snprintf_string(void)
{
    Suite *suite;

    TCase *tcase_pos;

    suite = suite_create("my_snprintf with string");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, ms_pos_string_default);
    tcase_add_test(tcase_pos, ms_pos_string_emtpy);
    tcase_add_test(tcase_pos, ms_pos_string_two);
    tcase_add_test(tcase_pos, ms_pos_string_two_with_another_symbols);
    tcase_add_test(tcase_pos, ms_pos_string_not_enough);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}
