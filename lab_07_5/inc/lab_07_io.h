#ifndef _LAB_07_IO_H_

#define _LAB_07_IO_H_

#include <stdbool.h>

#include "macrologger.h"

#define MAX_FILENAME_LEN 30

#define FILENAME_IN_INDEX       1
#define FILENAME_OUT_INDEX      2
#define FILTER_INDEX            3

#define OKAY                    0
#define INCORRECT_ARG_COUNT     1
#define INCORRECT_FILTER_KEY    2

typedef struct
{
    char *filename_in;
    char *filename_out;
    bool need_filter;
} args_fileds_t;

/**
 * @brief Parse command file args
 *
 * @return OKAY if all args correctly parsed;
 * INCORRECT_ARG_COUNT if incorrect args count;
 * INCORRECT_FILTER_KEY if filter key is incorrect;
 */
int parce_args(const int argc, char **argv, args_fileds_t *data);

#endif // _LAB_07_IO_H_
