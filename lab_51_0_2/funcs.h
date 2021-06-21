#ifndef _FUNCS_H_
#define _FUNCS_H_

#include <stdio.h>
#include <math.h>

#define OKAY 0
#define INCORRECT_SYMBOL -1
#define NOT_ENOUGH_NUM -2

int find_avg_value(FILE *f, float *avg);

int find_similar(FILE *f, const float avg, float *similar);

#endif
