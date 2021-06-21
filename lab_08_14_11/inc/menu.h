#ifndef __MENU_H__

#define __MENU_H__

#include "../inc/matrix.h"
#include "../inc/matrix_methods.h"
#include "../inc/args.h"

#define OKAY                            0
#define ALLOCATION_FAULT                128
#define MATRIXES_ISNOT_SUIT             129
#define PRINT_FAILED                    130
int menu_case_sum(char *fm_filename, char *sm_filename, char *out_filename);

#define OKAY                            0
#define ALLOCATION_FAULT                128
#define MATRIXES_ISNOT_SUIT             129
#define PRINT_FAILED                    130
int menu_case_multiple(char *fm_filename, char *sm_filename,
char *out_filename);

#define OKAY                            0
#define ALLOCATION_FAULT                128
#define PRINT_FAILED                    130
int menu_case_inverse(char *in_filename, char *out_filename);

#define OKAY                            0
#define MENU_CASE_SUM_FAILED            1
#define MENU_CASE_MULTIPLE_FAILED       2
#define MENU_CASE_INVERT_FAILED         3
#define NEVER_GET_HERE                  128
int menu(args_t *args);

#endif // __MENU_H__
