#include "../inc/numbers.h"

node_t *number_node_create(number_t data)
{
    node_t *node = malloc(sizeof(node_t));

    if (NULL != node)
    {
        number_t *data_ptr = malloc(sizeof(number_t));

        if (NULL != data_ptr)
        {
            node->data = data_ptr;
            *((number_t * ) node->data) = data;
            node->next = NULL;

            return node;
        }
        else
        {
            LOG_ERROR("%s", "Unable to allocate number_t");
            return NULL;
        }
    }
    else
    {
        LOG_INFO("%s", "Unable to allocate node_t");
        return NULL;
    }
}

bool is_args_correct_file_to_list_by_fptr(FILE *f, node_t **head)
{
    if (NULL == f)
    {
        LOG_ERROR("%s", "FILE *f is NULL");
        return false;
    }

    if (NULL == head)
    {
        LOG_ERROR("%s", "**head is NULL");
        return false;
    }

    if (NULL != *head)
    {
        LOG_ERROR("%s", "Given list isnot empty");
        return false;
    }

    return true;
}

int file_to_list_by_fptr(FILE *f, node_t **head)
{
    LOG_TRACE("%s", ">> Called");
    int rc;
    if (!is_args_correct_file_to_list_by_fptr(f, head))
    {
        LOG_ERROR("%s", "Incorrect args");
        return INCORRECT_ARGS;
    }

    int num;
    while (1 == (rc = fscanf(f, "%d", &num)))
    {
        LOG_DEBUG("Number scanned %d", num);
        number_t number = {.num = num};
        node_t *node = number_node_create(number);

        if (NULL == node)
        {
            LOG_ERROR("Unable to allocate node_t for num %d", num);
            list_free(head);
            *head = NULL;
            return ALLOCATION_FAILED;
        }

        list_append(head, node);
    }

    LOG_INFO("rc of fscanf is %d", rc);

    LOG_TRACE("%s", "<< Default return");
    return OKAY;
}

bool is_args_correct_file_to_list_by_filename(char *filename, node_t **head)
{
    if (NULL == filename)
    {
        LOG_ERROR("%s", "*filename is NULL");
        return false;
    }

    if (NULL == head)
    {
        LOG_ERROR("%s", "**head is NULL");
        return false;
    }

    if (NULL != *head)
    {
        LOG_ERROR("%s", "Given list isnot empty");
        return false;
    }

    return true;
}

int file_to_list_by_filename(char *filename, node_t **head)
{
    LOG_INFO(">> filename is %s", filename);

    if (!is_args_correct_file_to_list_by_filename(filename, head))
    {
        LOG_ERROR("%s", "Incorrect args");
        return INCORRECT_ARGS;
    }

    int rc, grc = OKAY;
    FILE *f = fopen(filename, "r");

    if (NULL == f)
    {
        LOG_ERROR("%s: %s", filename, strerror(errno));
        return UNABLE_TO_OPEN_FILE;
    }

    if (OKAY != (rc = file_to_list_by_fptr(f, head)))
    {
        LOG_ERROR("%s", "Node allocation failed");
        grc = rc;
    }

    LOG_INFO("List len = %zu", list_len(*head));

    if (EOF == fclose(f))
    {
        LOG_ERROR("fclose for %s failed", filename);
        list_free(head);
        grc = FCLOSE_FAILED;
    }

    LOG_INFO("<< grc = %d", grc);
    return grc;
}

int number_comparator(const void *data_f, const void *data_s)
{
    int num_f = ((const number_t *) data_f)->num;
    int num_s = ((const number_t *) data_s)->num;

    LOG_DEBUG("num_f = %d; num_s = %d", num_f, num_s);

    return num_f > num_s ? 1 : num_f == num_s ? 0 : -1;
}

void list_to_source_by_fptr(node_t *head, FILE *source)
{
    while (NULL != head)
    {
        fprintf(source, "%d\n", ((number_t *) head->data)->num);
        head = head->next;
    }
}

void number_node_free(node_t **head)
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

    free((*head)->data);
    free(*head);

    *head = NULL;
}

void number_list_free(node_t **head)
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
        number_node_free(&pre_node);
        pre_node = node;
        node = pre_node->next;
    }

    number_node_free(&pre_node);
    LOG_TRACE("%s", "<< Bye");
}
