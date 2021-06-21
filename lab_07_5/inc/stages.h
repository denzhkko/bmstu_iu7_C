#ifndef __PROCESS_H__

#define __PROCESS_H__

#include <stdlib.h>
#include <stdbool.h>

#include "../inc/macrologger.h"
#include "../inc/errors.h"

#include "../inc/lab_07_io.h"
#include "../inc/array_io.h"
#include "../inc/darray.h"
#include "../inc/lab_07_array.h"

int process_rc(const char *const funcname, const int return_code);

#define OKAY                            0
#define COUNTING_INTS_FAILED            1
#define ZERO_SRC_ARRAY_LEN              2 
#define ARRAY_ALLOCATION_FAILED         3
#define READ_INTS_FROM_FILE_FAILED      4
int stage_input(char *filename_in, darray_int_t **darr);

#define OKAY                            0
#define INCORRECT_ARRAY_FOR_FILTER      1
#define FILTER_ARRAY_FAILED             2
int stage_process(darray_int_t *darr, bool need_filter);

#define OKAY                            0
#define WRITING_ARRAY_FAILED            1
int stage_output(darray_int_t *darr, char *filename_out);

#endif // __PROCESS_H__
