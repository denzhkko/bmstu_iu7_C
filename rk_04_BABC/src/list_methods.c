#include "../inc/list_methods.h"

char_list_t *char_list_node_alloc(char c)
{
    char_list_t *node = malloc(sizeof(char_list_t));

    if (node)
    {
        node->symbol = c;
    }

    return node;
}

void char_list_free(char_list_t *head)
{
    char_list_t *node, *next;

    LIST_FOR_EACH_ENTRY_SAFE(node, next, &head->list, list, char_list_t)
    {
        list_del(&node->list);
        free(node);
    }

    free(head);
}

char_list_t *char_list_read(char *filename)
{
    FILE *f = fopen(filename, "r");

    if (NULL == f)
    {
        return NULL;
    }

    char_list_t *head = malloc(sizeof(char_list_t));

    if (NULL == head)
    {
        return NULL;
    }
    
    INIT_LIST_HEAD(&head->list);

    int c;

    char_list_t *node;

    while (EOF != (c = fgetc(f)))
    {
        node = char_list_node_alloc('\n' == c ? ' ' : c);

        if (NULL == node)
        {
            char_list_free(head);
            fclose(f);
            return NULL;
        }

        list_add_tail(&node->list, &head->list);
    }

    fclose(f);
    return head;
}

void char_list_print_to_source(FILE *f, char_list_t *head)
{
    char_list_t *node;
    LIST_FOR_EACH_ENTRY(node, &head->list, list, char_list_t)
    {
        fprintf(f, "%c", node->symbol);
    }

    fprintf(f, "\n");
}

int char_list_print(char *filename, char_list_t *head)
{
    FILE *f = fopen(filename, "w");

    if (NULL == f)
    {
        return FILE_CANNOT_BE_OPENED;
    }

    char_list_t *node;
    LIST_FOR_EACH_ENTRY(node, &head->list, list, char_list_t)
    {
        fprintf(f, "%c", node->symbol);
    }

    fprintf(f, "\n");

    fclose(f);

    return OKAY;
}

int reverse(char_list_t *head)
{
    char word[WORD_LEN + 1];
    int word_len = 0;

    char_list_t *word_start = NULL, /**word_end,*/ *node, *next, *word_node;

    LIST_FOR_EACH_ENTRY_SAFE(node, next, &head->list, list, char_list_t)
    {
        if (word_start == NULL)
        {
            word_start = node;
            word[word_len++] = node->symbol;
            LOG_DEBUG("Added new char: %c; word_len = %d", word[word_len - 1], word_len);
        }

        if (&next->list == &head->list || ' ' == next->symbol)
        {
            word[word_len++] = node->symbol;
            LOG_DEBUG("Added new char: %c; word_len = %d", word[word_len - 1], word_len);

            LOG_DEBUG("%s", "Word end");
            // word_end = node;

            for (word_node = word_start; ;
            word_node = LIST_ENTRY(&word_node->list.next, char_list_t, list))
            {
#if LOG_LEVEL  >= DEBUG_LEVEL
                for (int i = 0; i < word_len; ++i)
                    fprintf(stderr, "%c", word[i]);
                fprintf(stderr, "\n");
                char_list_print_to_source(stderr, head);
#endif
                LOG_DEBUG("word[i] = %c\n", word[word_len - 1]);
                word_node->symbol = word[word_len - 1];
                --word_len;

                if (word_len < 0)
                    break;
            }
            
            word_len = 0;
            word_start = NULL;
        }
    }

    return OKAY;
}
