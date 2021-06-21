#ifndef __STRIO_H__

#define __STRIO_H__

#include <stdio.h>

#include "macrologger.h"

#define SCANF_SIZE_T_EOF                EOF
#define SCANF_SIZE_T_FAILED             0
#define SCANF_SIZE_T_SUCCESS            1
int scanf_size_t(FILE *source, size_t *value);

#endif // __STRIO_H__
