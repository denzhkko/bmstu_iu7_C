#ifndef __LISTMATH_H__
#define __LISTMATH_H__

#include <assert.h>
#include <stdlib.h>

#include "rc.h"
#include "list.h"
#include "list_extension.h"
#include "macrologger.h"

#include "prime_num.h"
#include "mymath.h"

struct num_node
{
    unsigned power;
    struct list_head list;
};

struct num_node *num_to_listnum(unsigned num);

struct num_node *listnum_copy(struct num_node *head);

unsigned listnum_to_num(struct num_node *head);

void listnum_free(struct num_node *head);

void listnum_print(FILE *source, struct num_node *head);

struct num_node *listnum_mul(struct num_node *f_head, struct num_node *s_head);

struct num_node *listnum_sqr(struct num_node *head);

int listnum_div(struct num_node *f_head, struct num_node *s_head,
struct num_node **div);

#endif // __LISTMATH_H__
