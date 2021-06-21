#ifndef _FUNCS_H_
#define _FUNCS_H_

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#include "macrologger.h"
#include "errors.h"

#include "vector.h"
#include "product.h"
#include "vector_methods.h"

#define ARG_COUNT                       3
#define ARG_NUM_INPUT_RC                1
#define ARG_FILENAME_INDEX              1
#define ARG_PRICE_INDEX                 2

typedef struct args args_t;

struct args
{
    char *filename;
    double entered_price;
};

#define OKAY                            0
#define INCORRECT_ARG_COUNT             0x01
#define ARG_PRICE_NAN                   0x02
#define NOTPOSITIVE_ARG_PRICE           0x03
/**
 * @brief Arg parsing
 *
 * @return OKAY if success;
 * INCORRECT_ARG_COUNT if incorrect args count;
 * ARG_PRICE_NAN if arg price not a number;
 * NOTPOSITIVE_ARG_PRICE if arg price is not positive;
 */
int parse_args(int argc, char **argv, args_t *args);

/**
 * @return Main func return code based on func return codes
 */
int process_rc(char *funcname, int rc);

// EOF
#define OKAY                            0
#define NEGATIVE_NUM                    0x10
int check_curr_char_not_minus(FILE *const f);

// EOF
#define OKAY                            0
#define NEGATIVE_NUM                    0x10
#define NUM_GET_FAILED                  0x11
#define INCORRECT_FILE                  0x20
int read_size_t(FILE *const f, size_t *const num);

// EOF
#define OKAY                            0
#define INCORRECT_FILE                  0x20
#define ALLOCATION_FAILED               0x30
int read_product_name(FILE *const f, product_t *const item, char **buffer,
size_t *buffer_len);

// EOF
#define OKAY                            0
#define NEGATIVE_NUM                    0x10
#define NUM_GET_FAILED                  0x11
#define INCORRECT_FILE                  0x20
#define ALLOCATION_FAILED               0x30
int read_product(FILE *const f, product_t *const item, char **buffer,
size_t *buffer_len);

#define OKAY                            0
#define TITLE_NUM_GET_FAILED            0x12
#define TITLE_NUM_VECTOR_LEN_NE         0x13
#define INCORRECT_FILE                  0x20
#define FILE_NOT_FOUND                  0x21
#define FCLOSE_FAILED                   0x22
#define ALLOCATION_FAILED               0x30
#define VECTOR_APPEND_FAILED            0x31
int get_product_vector(char *filename, vector_t **vector);

#endif // _FUNCS_H_
