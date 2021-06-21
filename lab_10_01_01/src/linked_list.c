#include "../inc/linked_list.h"

node_t *node_create(void *data)
{
    node_t *node = malloc(sizeof(node_t));

    if (NULL != node)
    {
        node->data = data;
        node->next = NULL;
    }
    else
    {
        LOG_INFO("%s", "Unable to allocate node_t");
    }

    return node;
}

void list_append(node_t **head, node_t *node)
{
    assert(NULL != head);

    if (NULL == *head)
    {
        *head = node;
        return;
    }

    node_t *ptr = *head;

    while (NULL != ptr->next)
    {
        ptr = ptr->next;
    }

    ptr->next = node;
}

size_t list_len(node_t *head)
{
    size_t len = 0;

    while (NULL != head)
    {
        ++len;
        head = head->next;
    }

    return len;
}

void node_free(node_t **head)
{
    if (NULL == head)
    {
        LOG_WARNING("%s", "**head is NULL");
        return;
    }

    if (NULL == *head)
    {
        LOG_WARNING("%s", "*head is NULL");
        return;
    }

    free(*head);

    *head = NULL;
}

void list_free(node_t **head)
{
    LOG_TRACE("%s", ">> Called");
    assert(NULL != head);

    if (NULL == *head)
    {
        LOG_WARNING("%s", "List actually is empty");
        return;
    }

    node_t *pre_node = *head, *node = pre_node->next;

    while (NULL != node)
    {
        node_free(&pre_node);
        pre_node = node;
        node = pre_node->next;
    }

    node_free(&pre_node);
    LOG_TRACE("%s", "<< Bye");
}


int copy(node_t *head, node_t **new_head)
{
    if (NULL == new_head || NULL != *new_head)
    {
        LOG_ERROR("%s", "**new_head is NULL");
        return INCORRECT_ARGS;
    }

    if (NULL == head)
    {
        *new_head = NULL;
        return EMPTY_LIST;
    }

    *new_head = node_create(head->data);

    if (NULL == *new_head)
    {
        LOG_ERROR("%s", "Allocation failed");
        return ALLOCATION_FAILED;
    }

    node_t *node_new = *new_head;

    while (NULL != (head = head->next))
    {
        node_new->next = node_create(head->data);

        if (NULL == node_new->next)
        {
            LOG_ERROR("%s", "Allocation failed");
            list_free(new_head);
            return ALLOCATION_FAILED;
        }

        node_new = node_new->next;
    }

    return OKAY;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    LOG_TRACE(">> Called (*head == %p; *elem = %p; *before = %p)",
    (void *) *head, (void *) elem, (void *) before);

    if (*head == before)
    {
        elem->next = *head;
        *head = elem;

        LOG_TRACE("%s", "Element inserted to the 1st position");
        return;
    }

    node_t *node = *head;

    while (NULL != node && node->next != before)
    {
        node = node->next;
    }

    if (NULL == node && NULL != before)
    {
        LOG_ERROR("%s", "Before_node not found");
        return;
    }

    elem->next = node->next;
    node->next = elem;

    LOG_TRACE("%s", "<< Bye");
}

void sorted_insert(node_t **head, node_t *element,
int (*comparator)(const void *, const void *))
{
    LOG_TRACE("%s", ">> Called");

    if (NULL == *head || comparator(element->data, (*head)->data) < 0)
    {
        insert(head, element, *head);
        LOG_TRACE("%s", "<< element inserted to the 1st pos");
        return;
    }

    LOG_TRACE("%s", "First list node is less than curr");

    node_t *node = (*head)->next;

    LOG_TRACE("Link to second node = %p", (void *) node);

    while (NULL != node && comparator(node->data, element->data) < 0)
    {
        node = node->next;
    }

    insert(head, element, node);

    LOG_TRACE("%s", "<< Bye");
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    LOG_TRACE("%s", ">> Called");

    node_t *new_head = NULL;
    node_t *tmp_node;

    while (NULL != head)
    {
        LOG_TRACE("new_head = %p", (void *) new_head);

        tmp_node = head;
        head = head->next;
        sorted_insert(&new_head, tmp_node, comparator);
    }

    LOG_TRACE("%s", "<< Bye");
    return new_head;
}

void *pop_front(node_t **head)
{
    if (NULL == head || NULL == *head)
    {
        LOG_ERROR("%s", "**head or *head is NULL");
        return NULL;
    }

    node_t *node = *head;
    *head = (*head)->next;
    void *data = node->data;
    node_free(&node);

    return data;
}

void remove_duplicates(node_t **head,
int (*comparator)(const void *, const void *))
{
    if (NULL == *head)
    {
        LOG_INFO("%s", "List is empty");
        return;
    }

    node_t *node = *head;

    while (NULL != node->next)
    {
        if (0 == comparator(node->data, node->next->data))
        {
            node_t *duplicate = node->next;
            node->next = node->next->next;
            node_free(&duplicate);
        }
        else
        {
            node = node->next;
        }
    }
}
