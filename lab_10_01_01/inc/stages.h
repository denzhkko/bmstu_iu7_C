#ifndef __STAGES_H__

#define __STAGES_H__

#include <stdio.h>
#include <string.h>

#include "../inc/linked_list.h"
#include "../inc/numbers.h"
#include "../inc/labio.h"

#define EMPTY_FILE                      5
int run_stages(args_t *args);

int stage_input(char *filename, node_t **head);

#define OKAY                            0
#define ALLOCATION_FAILED               3
int stage_process(node_t **head, node_t **head_uniq);

#define OKAY                            0
#define UNABLE_TO_CLOSE_FILE            4
int stage_output(node_t *head, node_t *head_uniq,
char *filename, char *filename_uniq);

#endif // __STAGES_H__
