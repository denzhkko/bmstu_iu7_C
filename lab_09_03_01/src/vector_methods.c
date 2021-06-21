#include "../inc/vector_methods.h"

int vector_filter(vector_t *vector, const double entered_price)
{
    int rc;
    size_t shift_count = 0;
    size_t len = vector_get_length(vector);

    if (0 == len)
    {
        LOG_ERROR("%s", "Len is zero");
        return OKAY;
    }

    for (size_t i = len - 1; ; --i)
    {
        product_t product = vector_get_product_at(vector, i);

        if (product.price >= entered_price)
        {
            LOG_INFO("product price is %zu; delete is", product.price);

            vector_product_shift(vector, i);

            ++shift_count;
        }

        if (0 == i)
            break;
    }

    if (OKAY != (rc = vector_reallocate(vector, len - shift_count)))
        return rc;

    return OKAY;
}

int vector_print(vector_t *vector)
{
    assert(NULL != vector);

    size_t len = vector_get_length(vector);

    if (0 == len)
        return TARGET_PRODUCT_NOT_EXIST;

    for (size_t i = 0; i < len; ++i)
    {
        product_t product = vector_get_product_at(vector, i);
        printf("%s\n%zu\n", product.name, product.price);
    }

    return OKAY;
}
