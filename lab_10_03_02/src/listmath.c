#include "../inc/listmath.h"

struct num_node *num_to_listnum(unsigned num)
{
    assert(0 != num);

    LOG_INFO(">> num = %u", num);
    struct num_node *head = malloc(sizeof(struct num_node));

    if (NULL == head)
    {
        LOG_ERROR("%s", "Allocation failed");
        return NULL;
    }

    INIT_LIST_HEAD(&head->list);

    unsigned prime_num = 2, power;
    struct num_node *node;

    if (1 == num)
    {
        node = malloc(sizeof(struct num_node));

        if (NULL == node)
        {
            LOG_ERROR("%s", "Allocation failed");
            listnum_free(head);
            return NULL;
        }

        node->power = 0;
        list_add_tail(&node->list, &head->list);
    }

    while (1 != num)
    {
        LOG_TRACE("external loop started; num = %u; prime_num = %u", num,
        prime_num);

        power = 0;

        while (0 == num % prime_num)
        {
            LOG_TRACE("internal loop started; num = %u; "
            "num %% prime_num = %u; power = %u", num, num % prime_num, power);

            ++power;
            num /= prime_num;

            LOG_TRACE("internal loop ended; num = %u; "
            "num %% prime_num = %u; power = %u", num, num % prime_num, power);
        }

        node = malloc(sizeof(struct num_node));

        if (NULL == node)
        {
            LOG_ERROR("%s", "Allocation failed");
            listnum_free(head);
            return NULL;
        }

        node->power = power;
        list_add_tail(&node->list, &head->list);
        
        prime_num = (unsigned) next_prime_num(prime_num);

        LOG_TRACE("external loop ended; num = %u; prime_num = %u", num,
        prime_num);
    }

    return head;
}

struct num_node *listnum_copy(struct num_node *head)
{
    assert(NULL != head);

    struct num_node *new_head = malloc(sizeof(struct num_node));

    if (NULL == new_head)
    {
        LOG_ERROR("%s", "Allocation failed");
        return NULL;
    }

    INIT_LIST_HEAD(&new_head->list);

    struct num_node *node, *new_node;

    LIST_FOR_EACH_ENTRY(node, &head->list, list, struct num_node)
    {
        new_node = malloc(sizeof(struct num_node));

        if (NULL == new_node)
        {
            LOG_ERROR("%s", "Allocation failed");
            listnum_free(new_head);
            return NULL;
        }

        new_node->power = node->power;
        list_add_tail(&new_node->list, &new_head->list);
    }

    LOG_DEBUG("<< old = %u; new = %u",
    listnum_to_num(head), listnum_to_num(new_head));

    return new_head;
}

unsigned listnum_to_num(struct num_node *head)
{
    /*
    if (list_empty(&head->list))
    {
        LOG_WARNING("%s", "<< List is empty, num is 0");
        return 0;
    }
    */

    unsigned res = 1;
    struct num_node *node;
    unsigned prime_num = 2;

    LIST_FOR_EACH_ENTRY(node, &head->list, list, struct num_node)
    {
        res *= upow(prime_num, node->power);

        prime_num = (unsigned) next_prime_num(prime_num);
    }

    LOG_INFO("<< num = %u", res);
    return res;
}

void listnum_free(struct num_node *head)
{
    if (NULL == head)
        return;

    struct num_node *curr, *next;

    LIST_FOR_EACH_ENTRY_SAFE(curr, next, &head->list, list, struct num_node)
    {
        list_del(&curr->list);
        free(curr);
    }

    free(head);
}

void listnum_print(FILE *source, struct num_node *head)
{
    struct num_node *curr;

    LIST_FOR_EACH_ENTRY(curr, &head->list, list, struct num_node)
    {
        fprintf(source, "%u ", curr->power);
    }

    fprintf(source, "L\n");
}

struct num_node *listnum_mul(struct num_node *f_head, struct num_node *s_head)
{
    size_t f_len = list_len(&f_head->list);
    size_t s_len = list_len(&s_head->list);

    struct num_node *max_head = f_len > s_len ? f_head : s_head;
    struct num_node *min_head = f_len > s_len ? s_head : f_head;

    struct num_node *composition = listnum_copy(max_head);
    
    if (NULL == composition)
    {
        LOG_ERROR("%s", "Allocation failed");
        return NULL;
    }
    LOG_DEBUG("prev comp = %u", listnum_to_num(composition));

    struct num_node *comp_node, *min_node;

    TWO_LIST_FOR_EACH_ENTRY(comp_node, min_node, &composition->list,
    &min_head->list, list, struct num_node)
    {
        comp_node->power += min_node->power;
    }

    return composition;
}

struct num_node *listnum_sqr(struct num_node *head)
{
    struct num_node *new_head = listnum_copy(head);

    if (NULL == new_head)
    {
        LOG_ERROR("%s", "Allocation failed");
        return NULL;
    }
    struct num_node *new_node;

    LIST_FOR_EACH_ENTRY(new_node, &new_head->list, list, struct num_node)
    {
        new_node->power *= 2;
    }

    return new_head;
}

int listnum_div(struct num_node *f_head, struct num_node *s_head,
struct num_node **div)
{
    unsigned f_num = listnum_to_num(f_head);
    unsigned s_num = listnum_to_num(s_head);

    unsigned div_num = f_num / s_num;
    LOG_DEBUG("div_num = %u", div_num);

    if (0 == div_num)
    {
        LOG_ERROR("%s", "Res is zero");
        *div = NULL;
        return ERR_ZERO_GOT;
    }

    *div = num_to_listnum(div_num);

    if (NULL == *div)
    {
        LOG_ERROR("%s", "Allocation failed");
        return ERR_ALLOCATION_FAILED;
    }

    return OKAY;
}
