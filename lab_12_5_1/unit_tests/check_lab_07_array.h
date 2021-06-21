#ifndef _CHECK_LAB_07_ARRAY_H_

#define _CHECK_LAB_07_ARRAY_H_

#include <check.h>
#include <stdlib.h>
#include "../inc/lab_07_array.h"

#define OKAY                            0
#define MALLOC_FAULED                   1
#define DIFFERENT_ARRAYS                2

Suite *suite_create_key(void);

Suite *suite_create_compare_int(void);

Suite *suite_create_mysort(void);

#endif // _CHECK_LAB_07_ARRAY_H_
