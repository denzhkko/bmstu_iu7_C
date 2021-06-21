#ifndef __PRODUCT_H__

#define __PRODUCT_H__

#include <string.h>

#include "vector.h"

#define OKAY                            0
#define REALLOCATION_FAILED             0x32

typedef struct product product_t;

struct product
{
    char *name;
    size_t price;
};

product_t vector_get_product_at(const vector_t *vector, const size_t index);

void vector_set_product_at(const vector_t *vector, const size_t index,
const product_t product);

int vector_append_product(vector_t *vector, product_t product);

void product_item_free(product_t *product);

void product_vector_free(vector_t *vector);

void vector_product_shift(vector_t *vector, size_t index);

#endif // __PRODUCT_H__
