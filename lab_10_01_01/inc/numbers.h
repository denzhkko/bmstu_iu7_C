#ifndef __NUMBERS_H__

#define __NUMBERS_H__

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>

#include "macrologger.h"

#include "linked_list.h"

typedef struct number number_t;

struct number
{
    int num;
};

node_t *number_node_create(number_t data);

#define OKAY                            0
#define INCORRECT_ARGS                  2
#define ALLOCATION_FAILED               3
int file_to_list_by_fptr(FILE *f, node_t **head);

#define OKAY                            0
#define UNABLE_TO_OPEN_FILE             1
#define INCORRECT_ARGS                  2
#define ALLOCATION_FAILED               3
#define FCLOSE_FAILED                   4
int file_to_list_by_filename(char *filename, node_t **head);

int number_comparator(const void *data_f, const void *data_s);

void list_to_source_by_fptr(node_t *head, FILE *source);

void number_node_free(node_t **head);

void number_list_free(node_t **head);

#endif // __NUMBERS_H__
