#ifndef __LABIO_H__

#define __LABIO_H__

#include "macrologger.h"

#define ARGS_COUNT                      4
#define FILENAME_IN_INDEX               1
#define FILENAME_OUT_F_INDEX            2
#define FILENAME_OUT_S_INDEX            3

typedef struct
{
    char *filename_in;
    char *filename_out_f;
    char *filename_out_s;
} args_t;

#define OKAY                            0
#define INCORRECT_ARGS_COUNT            1

int parce_args(int argc, char **argv, args_t *args);

#endif // __LABIO_H__
