#ifndef __CHECK_SUPPORT_FUNCS_H__

#define __CHECK_SUPPORT_FUNCS_H__

#include <stdbool.h>
#include <assert.h>

#include "../inc/linked_list.h"

node_t *array_to_list(int *array, size_t array_len);

bool is_array_eq_list_by_value(node_t *head, int *array, size_t array_len);

bool is_array_eq_list_by_ptr(node_t *head, int *array, size_t array_len);

int int_comparator(const void *data_f, const void *data_s);

#endif // __CHECK_SUPPORT_FUNCS_H__
