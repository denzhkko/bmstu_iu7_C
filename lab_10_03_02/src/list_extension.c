#include "../inc/list_extension.h"

size_t list_len(struct list_head *head)
{
    size_t len = 0;

    struct list_head *node;

    LIST_FOR_EACH(node, head)
    {
        ++len;
    }

    return len;
}
