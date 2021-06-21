#ifndef __LIBDARR_H__

#define __LIBDARR_H__

#include <stdlib.h>
#include <assert.h>

#include "macrologger.h"

#define OKAY                            0
#define UNABLE_T0_CREATE_ARRAY          1
#define INDEX_OUT_OF_RANGE              2

struct darray_int;

typedef struct darray_int darray_int_t;

/**
 * @brief Create dynamic array
 *
 * @return OKAY if success;
 * UNABLE_T0_CREATE_ARRAY if malloc return NULL.
 */
int darray_int_init(darray_int_t **arr, const size_t length);

/**
 * @brief Delete dymanic array
 */
void darray_int_free(darray_int_t *array);

/**
 * @brief return value by index in array
 *
 * @return value by index i
 */
int darray_int_get(const darray_int_t *array, const size_t index);

/**
 * @brief Set value by index in array
 *
 * @return Nothing
 */
void darray_int_set(const darray_int_t *const array, const size_t index,
int const value);

/**
 * @brief Return length of dynamic array
 *
 * @return Length of dynamic array
 */
size_t darray_length(darray_int_t *array);

void darray_set_length(darray_int_t *array, const size_t new_len);

int *darray_get_data_ptr(darray_int_t *array);

void darray_set_data_ptr(darray_int_t *array, void *new_ptr);

#endif // __LIBDARR_H__
