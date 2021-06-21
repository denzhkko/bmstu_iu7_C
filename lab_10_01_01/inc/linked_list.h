#ifndef __LINKED_LIST__

#define __LINKED_LIST__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "macrologger.h"

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

node_t *node_create(void *data);

void list_append(node_t **head, node_t *node);

size_t list_len(node_t *head);

void node_free(node_t **head);

void list_free(node_t **head);

#define OKAY                            0
#define INCORRECT_ARGS                  2
#define ALLOCATION_FAILED               3
#define EMPTY_LIST                      6
int copy(node_t *head, node_t **new_head);

void insert(node_t **head, node_t *elem, node_t *before);

void sorted_insert(node_t **head, node_t *element,
int (*comparator)(const void *, const void *));

node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

void *pop_front(node_t **head);

void remove_duplicates(node_t **head,
int (*comparator)(const void *, const void *));

#endif // __LINKED_LIST__
