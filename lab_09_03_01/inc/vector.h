#ifndef __VECTOR_H__

#define __VECTOR_H__

#include <stdlib.h>
#include <assert.h>

#include "macrologger.h"

#define OKAY                            0
#define REALLOCATION_FAILED             0x32

typedef struct
{
    void *data;
    size_t length;

    size_t el_size;
} vector_t;

/**
 * @brief Create dynamic array
 *
 * @return pointer to vector if succes;
 * NULL if unable to allocate memory;
 */
vector_t *vector_allocate(const size_t length, const size_t el_size);

/**
 * @brief Frees up memory of vector and assing vector to NULL
 */
void vector_free(vector_t *vector);

/**
 * @brief Return pointer by index
 *
 * @return Pointer by index
 */
void *vector_get_ptr_to(const vector_t *vector, const size_t index);

/**
 * @brief Return int value by index in array
 *
 * @return int by index i
 */
int vector_get_int_at(const vector_t *vector, const size_t index);

/**
 * @brief return size_t value by index in array
 *
 * @return size_t by index i
 */
size_t vector_get_size_t_at(const vector_t *vector, const size_t index);

/**
 * @brief Set int value by index in array
 */
void vector_set_int_at(const vector_t *vector, const size_t index,
const int value);

/**
 * @brief Set size_t value by index in array
 */
void vector_set_size_t_at(const vector_t *vector, const size_t index,
const size_t value);

/**
 * @brief Return length of dynamic array
 *
 * @return Length of dynamic array
 */
size_t vector_get_length(vector_t *vector);

size_t vector_get_size(vector_t *vector);

int vector_append(vector_t *vector);

void vector_shift_item_by_index(vector_t *vector, size_t index);

int vector_reallocate(vector_t *vector, size_t new_len);

#endif // __VECTOR_H__
