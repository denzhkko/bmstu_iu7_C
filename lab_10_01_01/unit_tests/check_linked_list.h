#ifndef __CHECK_LINKED_LIST_H__

#define __CHECK_LINKED_LIST_H__

#include <check.h>
#include <limits.h>

#include "check_support_funcs.h"

#include "../inc/linked_list.h"
#include "../inc/numbers.h"

Suite *suite_create_node_create(void);

Suite *suite_create_list_append(void);

Suite *suite_create_list_len(void);

Suite *suite_create_copy(void);

Suite *suite_create_insert(void);

Suite *suite_create_sorted_insert(void);

Suite *suite_create_sort(void);

Suite *suite_create_pop_front(void);

Suite *suite_create_remove_duplicates(void);

#endif // __CHECK_LINKED_LIST_H__
