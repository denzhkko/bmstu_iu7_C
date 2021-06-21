#include "check_support_funcs.h"

node_t *array_to_list(int *array, size_t array_len)
{
    node_t *head = NULL;

    for (size_t i = 0; i < array_len; ++i)
    {
        node_t *node = node_create(array + i);

        if (NULL == node)
        {
            list_free(&head);
            return NULL;
        }

        list_append(&head, node);
    }

    return head;
}

bool is_array_eq_list_by_value(node_t *head, int *array, size_t array_len)
{
    if (array_len != list_len(head))
    {
        LOG_ERROR("$$ Array and list have diff len: %zu vs %zu",
        array_len, list_len(head));
        return false;
    }

    for (size_t i = 0; i < array_len; ++i)
    {
        if (array[i] != *((int *) head->data))
        {
            LOG_ERROR("$$ Diff values on index %zu; %d vs %d",
            i, array[i], *((int *) head->data));

            return false;
        }

        head = head->next;
    }

    return true;
}

bool is_array_eq_list_by_ptr(node_t *head, int *array, size_t array_len)
{
    if (array_len != list_len(head))
    {
        LOG_ERROR("$$ Array and list have diff len: %zu vs %zu",
        array_len, list_len(head));
        return false;
    }

    for (size_t i = 0; i < array_len; ++i)
    {
        if (array + i != head->data)
        {
            LOG_ERROR("$$ Diff ptr on index %zu; %p vs %p",
            i, (void *) (array + i), (void *) (head->data));

            return false;
        }

        head = head->next;
    }

    return true;
}

int int_comparator(const void *data_f, const void *data_s)
{
    int num_f = *((const int*) data_f);
    int num_s = *((const int*) data_s);

    LOG_DEBUG("num_f = %d; num_s = %d", num_f, num_s);

    return num_f > num_s ? 1 : num_f == num_s ? 0 : -1;
}
