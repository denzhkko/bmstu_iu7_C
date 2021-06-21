#ifndef __LABIO_H__

#define __LABIO_H__

#include <string.h>

#include "errors.h"
#include "args.h"

#include "menu.h"

#define APP_INDEX                       0
#define ACTION_INDEX                    1
#define FM_FILENAME_INDEX               2
#define SM_FILENAME_INDEX               3
#define OUT_FILENAME_INDEX              4

#define OKAY                            0
#define INCORRECT_ARGS                  1
int parse_args(int argc, char **argv, args_t *args);

int process_rc(const int return_code);

#endif // __LABIO_H__
