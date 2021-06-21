#include "../inc/libdarr.h"

struct darray_int
{
    int *elements;
    size_t length;
};

int darray_int_init(darray_int_t **arr, const size_t length)
{
    LOG_INFO(">> length == %zu", length);

    *arr = malloc(sizeof(struct darray_int));

    if (NULL == *arr)
    {
        LOG_ERROR("%s", "Unable to allocate memory for struct");
        *arr = NULL;

        return UNABLE_T0_CREATE_ARRAY;
    }

    int *arr_elems = (int *) malloc(length * sizeof(int));

    if (NULL == arr_elems)
    {
        (*arr)->elements = NULL;
        free(*arr);

        LOG_ERROR("<< Unable to create array with len %zu", length);
        return UNABLE_T0_CREATE_ARRAY;
    }

    (*arr)->elements = arr_elems;
    (*arr)->length = length;

    return OKAY;
}

void darray_int_free(darray_int_t *array)
{
    if (NULL == array)
    {
        LOG_INFO("%s", "array == NULL");
        return;
    }
    free(array->elements);
    free(array);
}

int darray_int_get(const darray_int_t *array, const size_t index)
{
    assert(index < array->length);

    return *(array->elements + index);
}

void darray_int_set(const darray_int_t *const array, const size_t index,
int const value)
{
    assert(index < array->length);

    *(array->elements + index) = value;
}

size_t darray_length(darray_int_t *array)
{
    return array->length;
}

void darray_set_length(darray_int_t *array, const size_t new_len)
{
    array->length = new_len;
}

int *darray_get_data_ptr(darray_int_t *array)
{
    return array->elements;
}

void darray_set_data_ptr(darray_int_t *array, void *new_ptr)
{
    array->elements = (int *) new_ptr;
}
