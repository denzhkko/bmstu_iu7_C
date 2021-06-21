#include "check_linked_list.h"

START_TEST(pos_nc)
{
    int num = 8;
    node_t *node = node_create(&num);
    ck_assert_ptr_nonnull(node);
    ck_assert_ptr_eq(&num, node->data);
    ck_assert_ptr_null(node->next);
    free(node);
}

Suite *suite_create_node_create(void)
{
    Suite *suite;
    TCase *tcase_pos;

    suite = suite_create("node_create");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pos_nc);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

START_TEST(pos_li_null_head)
{
    int num = 8;

    node_t *head = NULL;

    node_t *node = node_create(&num);
    ck_assert_ptr_nonnull(node);

    list_append(&head, node);

    ck_assert_ptr_eq(&num, head->data);
    ck_assert_ptr_null(head->next);

    free(head);
}
END_TEST

START_TEST(pos_li_nonnull_head)
{
    int num_f = 8, num_s = 32;

    node_t *head = node_create(&num_f);
    ck_assert_ptr_nonnull(head);

    node_t *node = node_create(&num_s);
    ck_assert_ptr_nonnull(node);

    list_append(&head, node);

    ck_assert_ptr_eq(&num_f, head->data);
    ck_assert_ptr_eq(head->next, node);
    ck_assert_ptr_eq(&num_s, head->next->data);
    ck_assert_ptr_null(head->next->next);

    free(node);
    free(head);
}
END_TEST

Suite *suite_create_list_append(void)
{
    Suite *suite;
    TCase *tcase_pos;

    suite = suite_create("list_append");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pos_li_null_head);
    tcase_add_test(tcase_pos, pos_li_nonnull_head);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

START_TEST(pos_ll_0)
{
    node_t *head = NULL;
    size_t len = list_len(head);
    ck_assert(0 == len);
}

#define ARRAY_LEN                       3
START_TEST(pos_ll_not_0)
{
    int arr[ARRAY_LEN] = {1, 2, 3};
    node_t *head = array_to_list(arr, ARRAY_LEN);
    ck_assert_ptr_nonnull(head);
    size_t len = list_len(head);
    ck_assert(len <= INT_MAX);
    ck_assert_int_eq(ARRAY_LEN, (int) len);
    list_free(&head);
}
#undef ARRAY_LEN

Suite *suite_create_list_len(void)
{
    Suite *suite;
    TCase *tcase_pos;

    suite = suite_create("list_len");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pos_ll_0);
    tcase_add_test(tcase_pos, pos_ll_not_0);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

START_TEST(neg_c_ptr_ptr_null)
{
    node_t *head_f = NULL;
    int rc = copy(head_f, NULL);
    ck_assert_int_eq(INCORRECT_ARGS, rc);
    ck_assert_ptr_null(head_f);
}
END_TEST

START_TEST(neg_c_empty)
{
    node_t *head_f = NULL, *head_s = NULL;
    int rc = copy(head_f, &head_s);
    ck_assert_int_eq(EMPTY_LIST, rc);
    ck_assert_ptr_null(head_s);
}
END_TEST

#define ARRAY_LEN                       3
START_TEST(pos_c_not_null)
{
    int array[ARRAY_LEN] = {1, 2, 3};
    node_t *head_f = array_to_list(array, ARRAY_LEN), *head_s = NULL;
    int rc = copy(head_f, &head_s);
    ck_assert_int_eq(OKAY, rc);
    rc = is_array_eq_list_by_value(head_f, array, ARRAY_LEN);
    ck_assert_int_eq(true, rc);
    rc = is_array_eq_list_by_value(head_s, array, ARRAY_LEN);
    ck_assert_int_eq(true, rc);
    list_free(&head_f);
    list_free(&head_s);
}
END_TEST
#undef ARRAY_LEN

Suite *suite_create_copy(void)
{
    Suite *suite;
    TCase *tcase_neg;
    TCase *tcase_pos;

    suite = suite_create("copy");

    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_neg, neg_c_ptr_ptr_null);
    tcase_add_test(tcase_neg, neg_c_empty);

    suite_add_tcase(suite, tcase_neg);

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pos_c_not_null);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

START_TEST(neg_i_before_not_found)
{
    node_t *head = NULL;
    int num = 64, another_num = 15;
    node_t *node = node_create(&num);
    ck_assert_ptr_nonnull(node);
    insert(&head, node, (node_t *) &another_num);
    ck_assert_ptr_null(head);
    ck_assert_ptr_eq(&num, node->data);
    ck_assert_ptr_null(node->next);
    free(node);
}

START_TEST(pos_i_null)
{
    node_t *head = NULL;
    int num = 64;
    node_t *node = node_create(&num);
    ck_assert_ptr_nonnull(node);
    insert(&head, node, head);
    ck_assert_ptr_eq(&num, head->data);
    ck_assert_ptr_null(head->next);
    free(node);
}

START_TEST(pos_i_before_first)
{
    int head_num = 2, insert_num = 1;
    node_t *head = node_create(&head_num);
    node_t *node = node_create(&insert_num);
    insert(&head, node, head);
    ck_assert_ptr_eq(&insert_num, head->data);
    ck_assert_ptr_eq(&head_num, head->next->data);
    ck_assert_ptr_null(head->next->next);
    list_free(&head);
}

START_TEST(pos_i_after_last)
{
    int head_num = 1, insert_num = 2;
    node_t *head = node_create(&head_num);
    node_t *node = node_create(&insert_num);
    insert(&head, node, head->next);
    ck_assert_ptr_eq(&head_num, head->data);
    ck_assert_ptr_eq(&insert_num, head->next->data);
    ck_assert_ptr_null(head->next->next);
    list_free(&head);
}

#define ARRAY_LEN                       2
START_TEST(pos_i_between)
{
    int array_src[ARRAY_LEN] = {1, 3};
    node_t *head = array_to_list(array_src, ARRAY_LEN);
    ck_assert_ptr_nonnull(head);
    int insert_num = 2;
    node_t *insert_node = node_create(&insert_num);
    insert(&head, insert_node, head->next);
    ck_assert_ptr_eq(array_src, head->data);
    ck_assert_ptr_eq(&insert_num, head->next->data);
    ck_assert_ptr_eq(array_src + 1, head->next->next->data);
    ck_assert_ptr_null(head->next->next->next);
    list_free(&head);
}
#undef ARRAY_LEN

Suite *suite_create_insert(void)
{
    Suite *suite;
    TCase *tcase_neg;
    TCase *tcase_pos;

    suite = suite_create("insert");

    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_neg, neg_i_before_not_found);

    suite_add_tcase(suite, tcase_neg);

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pos_i_null);
    tcase_add_test(tcase_pos, pos_i_before_first);
    tcase_add_test(tcase_pos, pos_i_after_last);
    tcase_add_test(tcase_pos, pos_i_between);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

START_TEST(pos_si_null)
{
    node_t *head = NULL;
    int num = 64;
    node_t *node = node_create(&num);
    ck_assert_ptr_nonnull(node);
    sorted_insert(&head, node, int_comparator);
    ck_assert_ptr_eq(&num, head->data);
    ck_assert_ptr_null(head->next);
    free(node);
}
END_TEST

START_TEST(pos_si_before_first)
{
    int head_num = 2, insert_num = 1;
    node_t *head = node_create(&head_num);
    node_t *node = node_create(&insert_num);
    sorted_insert(&head, node, int_comparator);
    ck_assert_ptr_eq(&insert_num, head->data);
    ck_assert_ptr_eq(&head_num, head->next->data);
    ck_assert_ptr_null(head->next->next);
    list_free(&head);
}

START_TEST(pos_si_after_last)
{
    int head_num = 1, insert_num = 2;
    node_t *head = node_create(&head_num);
    node_t *node = node_create(&insert_num);
    sorted_insert(&head, node, int_comparator);
    ck_assert_ptr_eq(&head_num, head->data);
    ck_assert_ptr_eq(&insert_num, head->next->data);
    ck_assert_ptr_null(head->next->next);
    list_free(&head);
}

#define ARRAY_LEN                       2
START_TEST(pos_si_between)
{
    int array_src[ARRAY_LEN] = {1, 3};
    node_t *head = array_to_list(array_src, ARRAY_LEN);
    ck_assert_ptr_nonnull(head);
    int insert_num = 2;
    node_t *insert_node = node_create(&insert_num);
    sorted_insert(&head, insert_node, int_comparator);
    ck_assert_ptr_eq(array_src, head->data);
    ck_assert_ptr_eq(&insert_num, head->next->data);
    ck_assert_ptr_eq(array_src + 1, head->next->next->data);
    ck_assert_ptr_null(head->next->next->next);
    list_free(&head);
}
#undef ARRAY_LEN

Suite *suite_create_sorted_insert(void)
{
    Suite *suite;
    TCase *tcase_pos;

    suite = suite_create("sorted_insert");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pos_si_null);
    tcase_add_test(tcase_pos, pos_si_before_first);
    tcase_add_test(tcase_pos, pos_si_after_last);
    tcase_add_test(tcase_pos, pos_si_between);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

START_TEST(pos_s_null)
{
    node_t *head = NULL;
    head = sort(head, int_comparator);
    ck_assert_ptr_null(head);
}

START_TEST(pos_s_one_elem)
{
    int num = 256;
    node_t *head = node_create(&num);
    ck_assert_ptr_nonnull(head);
    head = sort(head, int_comparator);
    ck_assert_ptr_eq(&num, head->data);
    ck_assert_ptr_null(head->next);
    free(head);
}

#define ARRAY_LEN                       2
START_TEST(pos_s_two_elems_sorted)
{
    int array[ARRAY_LEN] = {1, 2};
    node_t *head = array_to_list(array, ARRAY_LEN);
    ck_assert_ptr_nonnull(head);
    head = sort(head, int_comparator);
    bool rc = is_array_eq_list_by_ptr(head, array, ARRAY_LEN);
    ck_assert_int_eq(true, rc);
    list_free(&head);
}
#undef ARRAY_LEN

#define ARRAY_LEN                       2
START_TEST(pos_s_two_elems_unsorted)
{
    int array[ARRAY_LEN] = {2, 1};
    int array_dst[ARRAY_LEN] = {1, 2};
    node_t *head = array_to_list(array, ARRAY_LEN);
    ck_assert_ptr_nonnull(head);
    head = sort(head, int_comparator);
    bool rc = is_array_eq_list_by_value(head, array_dst, ARRAY_LEN);
    ck_assert_int_eq(true, rc);
    list_free(&head);
}
#undef ARRAY_LEN

#define ARRAY_LEN                       2
START_TEST(pos_s_two_elems_eq)
{
    int array[ARRAY_LEN] = {1, 2};
    int array_dst[ARRAY_LEN] = {1, 2};
    node_t *head = array_to_list(array, ARRAY_LEN);
    ck_assert_ptr_nonnull(head);
    head = sort(head, int_comparator);
    bool rc = is_array_eq_list_by_value(head, array_dst, ARRAY_LEN);
    ck_assert_int_eq(true, rc);
    list_free(&head);
}
#undef ARRAY_LEN

#define ARRAY_LEN                       10
START_TEST(pos_s_ten_elems)
{
    int array[ARRAY_LEN] = {55, -100, -1, -12, 0, 8000, 14, 1, 1001, 5555};
    int array_dst[ARRAY_LEN] = {-100, -12, -1, 0, 1, 14, 55, 1001, 5555, 8000};
    node_t *head = array_to_list(array, ARRAY_LEN);
    ck_assert_ptr_nonnull(head);
    head = sort(head, int_comparator);
    bool rc = is_array_eq_list_by_value(head, array_dst, ARRAY_LEN);
    ck_assert_int_eq(true, rc);
    list_free(&head);
}
#undef ARRAY_LEN

Suite *suite_create_sort(void)
{
    Suite *suite;
    TCase *tcase_pos;

    suite = suite_create("sort");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pos_s_null);
    tcase_add_test(tcase_pos, pos_s_one_elem);
    tcase_add_test(tcase_pos, pos_s_two_elems_sorted);
    tcase_add_test(tcase_pos, pos_s_two_elems_unsorted);
    tcase_add_test(tcase_pos, pos_s_two_elems_eq);
    tcase_add_test(tcase_pos, pos_s_ten_elems);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

START_TEST(neg_pf_null)
{
    node_t *head = NULL;

    node_t *poped = pop_front(&head);

    ck_assert_ptr_null(head);
    ck_assert_ptr_null(poped);
}
END_TEST

START_TEST(pos_pf_one_elem)
{
    int num = 1861;
    node_t *head = node_create(&num);

    node_t *poped_data = pop_front(&head);

    ck_assert_ptr_null(head);
    ck_assert_ptr_eq(&num, poped_data);
}
END_TEST

#define ARRAY_LEN                       2
START_TEST(pos_pf_two_elems)
{
    int array[ARRAY_LEN] = {0, 1};
    node_t *head = array_to_list(array, ARRAY_LEN);

    node_t *poped = pop_front(&head);

    ck_assert_ptr_nonnull(head);
    ck_assert_ptr_eq(array + 1, head->data);
    ck_assert_ptr_null(head->next);

    ck_assert_ptr_eq(array, poped);

    free(head);
}
END_TEST
#undef ARRAY_LEN

Suite *suite_create_pop_front(void)
{
    Suite *suite;
    TCase *tcase_neg;
    TCase *tcase_pos;

    suite = suite_create("pop_front");

    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_neg, neg_pf_null);

    suite_add_tcase(suite, tcase_neg);

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pos_pf_one_elem);
    tcase_add_test(tcase_pos, pos_pf_two_elems);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

START_TEST(neg_rd_null)
{
    node_t *head = NULL;
    remove_duplicates(&head, int_comparator);
    ck_assert_ptr_null(head);
}

START_TEST(pos_rd_one_elem)
{
    int num = 1917;
    node_t *head = node_create(&num);
    remove_duplicates(&head, int_comparator);
    ck_assert_ptr_eq(&num, head->data);
    ck_assert_ptr_null(head->next);
    free(head);
}

#define ARRAY_LEN                       3
START_TEST(pos_rd_three_uniq)
{
    int array[ARRAY_LEN] = {0, 1, 2};
    node_t *head = array_to_list(array, ARRAY_LEN);
    remove_duplicates(&head, int_comparator);
    bool rc = is_array_eq_list_by_ptr(head, array, ARRAY_LEN);
    ck_assert_int_eq(true, rc);
    list_free(&head);
}
#undef ARRAY_LEN

#define ARRAY_LEN                       2
START_TEST(pos_rd_two_eq)
{
    int array[ARRAY_LEN] = {2, 2};
    node_t *head = array_to_list(array, ARRAY_LEN), *copy_head = NULL;
    int rc = copy(head, &copy_head);
    ck_assert_int_eq(OKAY, rc);
    remove_duplicates(&copy_head, int_comparator);
    ck_assert_int_eq(1, (int) list_len(copy_head));
    ck_assert_int_eq(2, *((int *) copy_head->data));
    ck_assert_ptr_null(copy_head->next);
    list_free(&copy_head);
    list_free(&head);
}
#undef ARRAY_LEN

#define ARRAY_LEN                       3
START_TEST(pos_rd_three_eq)
{
    int array[ARRAY_LEN] = {2, 2, 2};
    node_t *head = array_to_list(array, ARRAY_LEN), *copy_head = NULL;
    int rc = copy(head, &copy_head);
    ck_assert_int_eq(OKAY, rc);
    remove_duplicates(&copy_head, int_comparator);
    ck_assert_int_eq(2, *((int *) copy_head->data));
    ck_assert_ptr_null(copy_head->next);
    list_free(&copy_head);
    list_free(&head);
}
#undef ARRAY_LEN

#define ARRAY_LEN                       3
START_TEST(pos_rd_three_mixed)
{
    int array[ARRAY_LEN] = {1, 2, 2};
    node_t *head = array_to_list(array, ARRAY_LEN), *copy_head = NULL;
    int rc = copy(head, &copy_head);
    ck_assert_int_eq(OKAY, rc);
    remove_duplicates(&copy_head, int_comparator);
    ck_assert_int_eq(1, *((int *) copy_head->data));
    ck_assert_int_eq(2, *((int *) copy_head->next->data));
    ck_assert_ptr_null(copy_head->next->next);
    list_free(&copy_head);
    list_free(&head);
}
#undef ARRAY_LEN

Suite *suite_create_remove_duplicates(void)
{
    Suite *suite;
    TCase *tcase_neg;
    TCase *tcase_pos;

    suite = suite_create("pop_front");

    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_neg, neg_rd_null);

    suite_add_tcase(suite, tcase_neg);

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, pos_rd_one_elem);
    tcase_add_test(tcase_pos, pos_rd_three_uniq);
    tcase_add_test(tcase_pos, pos_rd_two_eq);
    tcase_add_test(tcase_pos, pos_rd_three_eq);
    tcase_add_test(tcase_pos, pos_rd_three_mixed);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}
