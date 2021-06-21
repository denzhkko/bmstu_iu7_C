#ifndef __STAGES_H__
#define __STAGES_H__

#include <stdio.h>
#include <string.h>

#include "rc.h"
#include "macrologger.h"

#include "listmath.h"
#include "nonstdio.h"

#define STR_OUT                         "out"
#define STR_MUL                         "mul"
#define STR_SQR                         "sqr"
#define STR_DIV                         "div"
#define KEYWORD_STR_LEN                 3

#define CASE_UNKNOWN                    0xc0
#define CASE_OUT                        0xc1
#define CASE_MUL                        0xc2
#define CASE_SQR                        0xc3
#define CASE_DIV                        0xc4

struct args
{
    unsigned selected_case;
    unsigned num_1;
    unsigned num_2;
};

int run_stages();

#endif // __STAGES_H__
