#include <stdio.h>

#include "funcs.h"

#define NOT_ENOUGH_NUM_MES "Not enough numbers\n"
#define NO_ALPHA_AT_END_MES "No char at end\n"
#define UNKNOWN_EXIT_CODE_MES "Unknown error\n"

#define NOT_ENOUGH_NUM_ERROR 1
#define NO_ALPHA_AT_END_ERROR 2
#define UNKNOWN_EXIT_CODE_ERROR 3

int process_exit_code(const int exit_code)
{
    switch (exit_code)
    {
        case OKAY:
            return OKAY;
        case NOT_ENOUGH_NUM:
            printf(NOT_ENOUGH_NUM_MES);
            return NOT_ENOUGH_NUM_ERROR;
        default:
            printf(UNKNOWN_EXIT_CODE_MES);
            return UNKNOWN_EXIT_CODE_ERROR;
    }
}

int main(void)
{
    int max_len;
    int rc;

    if (OKAY == (rc = process(stdin, &max_len)))
        printf("%d\n", max_len);

    return process_exit_code(rc);
}
