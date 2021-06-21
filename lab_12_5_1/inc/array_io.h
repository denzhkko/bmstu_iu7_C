#ifndef _ARRAY_IO_H_

#define _ARRAY_IO_H_

#include <stdio.h>
#include <assert.h>

#include "macrologger.h"

#include "libdarr.h"

#define OKAY                            0
#define WRONG_SYMBOL_FOUND              1
#define FCLOSE_FAILED                   2
#define INCORRECT_FILE_NUM_COUNT        3
#define UNABLE_TO_OPEN_FILE             4

/**
 * @brief Count number in file
 *
 * @return OKAY if no error;
 * WRONG_SYMBOL_FOUND if in file wrong symbol found;
 * FCLOSE_FAILED if fclose failed;
 * UNABLE_TO_OPEN_FILE if unable to open file;
 */
int count_integers_in_file(const char *const filename,
size_t *const integer_count);

/**
 * @brief Read integers from file to array
 *
 * Read integers from file to dynamic array. Memory for array should be inited
 * before function called
 *
 * @return OKAY if no error;
 * UNABLE_TO_OPEN_FILE if unable to open file;
 * INCORRECT_FILE_NUM_COUNT if fsnanf return unexpected 1;
 * FCLOSE_FAILED if fclose failed;
 */
int file_to_array(const char *const fname, darray_int_t *const arr);

/**
 * @brief Print array data to file
 *
 * @return OKAY if success;
 * FCLOSE_FAILED if fclose failed;
 * UNABLE_TO_OPEN_FILE if unable to open file;
 */
int array_to_file(const char *const filename, darray_int_t *darr);

#endif // _ARRAY_IO_H_
