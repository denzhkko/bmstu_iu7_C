#ifndef _CHECK_ARRAY_IO_H_

#define _CHECK_ARRAY_IO_H_

#include <check.h>
#include "../inc/array_io.h"
#include "../inc/libdarr.h"

Suite *suite_create_count_integers_in_file(void);

Suite *suite_create_file_to_array(void);

#endif // _CHECK_ARRAY_IO_H_
