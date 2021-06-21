#include <stdio.h>

#include "funcs.h"

#define INCORRECT_START_MES "Please enter: ./main.exe <file-name>\n"
#define FILE_CANNOT_BE_OPENED_MES "File cannot be opened\n"
#define INCORRECT_SYMBOL_MES "Incorrect symbol\n"
#define NOT_ENOUGH_NUM_MES "Not enough numbers\n"
#define UNKNOWN_ERROR_MES "Unknown error\n"

#define INCORRECT_START_ERROR 1
#define FILE_CANNOT_BE_OPENED_ERROR 2
#define INCORRECT_SYMBOL_ERROR 3
#define NOT_ENOUGH_NUM_ERROR 4
#define UNKNOWN_ERROR 127

int process_exit_code(const int exit_code)
{
    switch (exit_code)
    {
        case OKAY:
            return OKAY;
        case INCORRECT_SYMBOL:
            printf(INCORRECT_SYMBOL_MES);
            return INCORRECT_SYMBOL_ERROR;
        case NOT_ENOUGH_NUM:
            printf(NOT_ENOUGH_NUM_MES);
            return NOT_ENOUGH_NUM_ERROR;
        default:
            printf(UNKNOWN_ERROR_MES);
            return UNKNOWN_ERROR;
    }
}

int main(int argc, char *argv[])
{
    int grc = UNKNOWN_ERROR, rc;

    if (2 == argc)
    {
        FILE *f = fopen(argv[1], "r");

        if (f)
        {
            float avg;
            rc = find_avg_value(f, &avg);

            if (OKAY == rc)
            {
                float similar;
                rc = find_similar(f, avg, &similar);

                if (OKAY == rc)
                {
                    printf("%.5f\n", similar);
                    grc = OKAY;
                }
                else
                    grc = process_exit_code(rc);
            }
            else
                grc = process_exit_code(rc);

            fclose(f);
        }
        else
        {
            printf(FILE_CANNOT_BE_OPENED_MES);
            grc = FILE_CANNOT_BE_OPENED_ERROR;
        }
    }
    else
    {
        printf(INCORRECT_START_MES);
        grc = INCORRECT_START_ERROR;
    }

    return grc;
}
