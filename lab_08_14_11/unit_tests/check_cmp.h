#ifndef __CHECK_CMP_H__

#define __CHECK_CMP_H__

#include <stdio.h>
#include <math.h>

#include "../inc/macrologger.h"

#include "../inc/double.h"

#define FILE_EQUAL                      0
#define FILE_NOT_EQUAL                  1
#define INCORRECT_FILE                  2
#define FILE_CANNOT_BE_OPENED           129
#define FCLOSE_FAILED                   130
int is_file_double_matrix_eq(char *f_filename, char *s_filename);

#endif // __CHECK_CMP_H__
