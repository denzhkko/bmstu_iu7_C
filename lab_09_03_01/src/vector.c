#include "../inc/vector.h"

vector_t *vector_allocate(const size_t length, const size_t el_size)
{
    LOG_INFO(">> length = %zu; el_size = %zu", length, el_size);
    assert(0 != el_size);

    vector_t *vector = (vector_t *) malloc(sizeof(vector_t));
    
    if (NULL == vector)
    {
        LOG_ERROR("<< Unable to allocate memory for vector_t [%zu B]",
        sizeof(vector_t));

        return NULL;
    }

    void *data;

    if (0 == length)
    {
        data = NULL;
        LOG_INFO("%s", "vector.data = NULL because length == 0");
    }
    else
    {
        data = malloc(length * el_size);

        if (NULL == data)
        {
            LOG_ERROR("Unable to allocate memory for data [%zu B]",
            length * el_size);

            free(vector);

            return NULL;
        }
    }

    vector->data = data;
    vector->length = length;
    vector->el_size = el_size;

    return vector;
}

void vector_free(vector_t *vector)
{
    if (NULL == vector)
    {
        LOG_WARNING("%s", "NULL == vector");
        return;
    }

    free(vector->data);

    free((void *) vector);

    vector = NULL;
}

void *vector_get_ptr_to(const vector_t *vector, const size_t index)
{
    assert(index < vector->length);

    return (void *) ((char *) vector->data + index * vector->el_size);
}

size_t vector_get_length(vector_t *vector)
{
    return vector->length;
}

int vector_append(vector_t *vector)
{
    vector->length++;
    vector->data = realloc(vector->data, vector->el_size * vector->length);

    if (NULL == vector->data)
    {
        LOG_ERROR("%s", "reallocation failed");
        return REALLOCATION_FAILED;
    }

    return OKAY;
}

int vector_reallocate(vector_t *vector, size_t new_len)
{
    vector->length = new_len;

    if (0 == new_len)
    {
        free(vector->data);
        vector->data = NULL;
        return OKAY;
    }

    vector->data = realloc(vector->data, new_len * vector->el_size);

    if (NULL == vector->data)
    {
        vector->length = 0;
        return REALLOCATION_FAILED;
    }

    return OKAY;
}
