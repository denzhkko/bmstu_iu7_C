#ifndef __CHECK_MATRIX_METHODS_H__

#define __CHECK_MATRIX_METHODS_H__

#include <check.h>

#include "../inc/matrix_methods.h"
#include "check_cmp.h"

Suite *suite_file_to_double_matrix(void);

Suite *suite_get_invert_double_matrix(void);

Suite *suite_get_double_matrix_sum(void);

Suite *suite_get_double_matrix_product(void);

Suite *suite_is_file_double_matrix_eq(void);

#endif // __CHECK_MATRIX_METHODS_H__
