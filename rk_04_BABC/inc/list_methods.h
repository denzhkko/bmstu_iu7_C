#ifndef __LIST_METHODS_H__
#define __LIST_METHODS_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#include "rc.h"
#include "../inc/macrologger.h"

#define WORD_LEN                        10

typedef struct
{
    char symbol;
    struct list_head list;
} char_list_t;

char_list_t *char_list_read(char *filename);

int char_list_print(char *filename, char_list_t *head);

int reverse(char_list_t *head);

#endif // __LIST_METHODS_H__
