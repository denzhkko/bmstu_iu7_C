#ifndef __CHECK_LISTMATH_H__
#define __CHECK_LISTMATH_H__

#include <stdbool.h>

#include <check.h>

#include "../inc/list.h"
#include "../inc/listmath.h"

Suite *suite_num_to_listnum(void);

Suite *suite_listnum_to_num(void);

Suite *suite_listnum_mul(void);

Suite *suite_listnum_copy(void);

Suite *suite_listnum_sqr(void);

Suite *suite_listnum_div(void);

#endif // __CHECK_LISTMATH_H__
