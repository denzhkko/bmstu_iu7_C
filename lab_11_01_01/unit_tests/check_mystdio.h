#ifndef __CHECK_MYSTDIO_H__
#define __CHECK_MYSTDIO_H__

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <check.h>

#include "../inc/mystdio.h"

Suite *suite_my_snprintf(void);

Suite *suite_my_snprintf_char(void);

Suite *suite_my_snprintf_int(void);

Suite *suite_my_snprintf_short(void);

Suite *suite_my_snprintf_string(void);

#endif // __CHECK_MYSTDIO_H__
