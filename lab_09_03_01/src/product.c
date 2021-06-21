#include "../inc/product.h"

product_t vector_get_product_at(const vector_t *vector, const size_t index)
{
    assert(sizeof(product_t) == vector->el_size);

    return *((product_t *) vector_get_ptr_to(vector, index));
}

void vector_set_product_at(const vector_t *vector, const size_t index,
const product_t product)
{
    assert(sizeof(product) == vector->el_size);

    *((product_t *) vector_get_ptr_to(vector, index)) = product;
}

int vector_append_product(vector_t *vector, product_t product)
{
    if (OKAY != vector_append(vector))
        return REALLOCATION_FAILED;

    vector_set_product_at(vector, vector->length - 1, product);

    return OKAY;
}

void product_item_free(product_t *product)
{
    free(product->name);
    product->name = NULL;
}

void product_vector_free(vector_t *vector)
{
    size_t len = vector_get_length(vector);

    for (size_t i = 0; i < len; ++i)
    {
        product_t product = vector_get_product_at(vector, i);
        product_item_free(&product);
    }

    vector_free(vector);
}

void vector_product_shift(vector_t *vector, size_t index)
{
    assert(0 != vector->length);
    assert(index < vector->length);

    product_t *ptr = vector_get_ptr_to(vector, index);
    free(ptr->name);

    memcpy(ptr, ptr + 1, vector->el_size * (vector->length - index - 1));
}
