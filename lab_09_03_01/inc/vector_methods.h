#ifndef __VECTOR_METHODS_H__
#define __VECTOR_METHODS_H__

#include <assert.h>
#include <stdbool.h>

#include "../inc/vector.h"
#include "../inc/product.h"

#define OKAY                            0
#define TARGET_PRODUCT_NOT_EXIST        0x04

int vector_filter(vector_t *vector, const double entered_price);

int vector_print(vector_t *vector);

#endif // __VECTOR_METHODS_H__
