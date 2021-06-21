#include <stdio.h>
#include <string.h>

#include "funcs.h"

int main(int argc, char **argv)
{
    FILE *f_in, *f_out;
    int grc = OKAY, rc;

    if (3 == argc)
    {
        if (0 == strcmp(argv[1], "ab"))
        {
            f_in = fopen(argv[2], "rb+");

            if (f_in)
            {
                // Append to sorted binary file
                if (OKAY != (rc = append_to_sorted_file(f_in)))
                    grc = process_exit_code(rc);

                if (EOF == fclose(f_in))
                    grc = process_exit_code(FCLOSE_FAILED);
            }
            else
                grc = process_exit_code(FILE_CANNOT_BE_OPENED);
        }
        else
            grc = process_exit_code(INCORRECT_PARAMETERS);
    }
    else if (4 == argc)
    {
        if (0 == strcmp(argv[1], "sb"))
        {
            f_in = fopen(argv[2], "rb");
            f_out = fopen(argv[3], "wb+");

            if (f_in)
            {
                if (f_out)
                {
                    // Sort binary file by prica and quantity
                    if (OKAY != (rc = sort_file(f_in, f_out)))
                        grc = process_exit_code(rc);

                    if (EOF == fclose(f_out))
                        grc = process_exit_code(FCLOSE_FAILED);
                }
                else
                    grc = process_exit_code(FILE_CANNOT_BE_OPENED);

                if (EOF == fclose(f_in))
                    grc = process_exit_code(FCLOSE_FAILED);
            }
            else
                grc = process_exit_code(FILE_CANNOT_BE_OPENED);
        }
        else if (0 == strcmp(argv[1], "fb"))
        {
            f_in = fopen(argv[2], "rb");

            if (f_in)
            {
                if (strlen(argv[3]) <= MAX_NAME_LEN)
                {
                    // Print products with substr at name end
                    if (OKAY != (rc = find_items(f_in, argv[3])))
                        grc = process_exit_code(rc);
                }
                else
                    grc = process_exit_code(INCORRECT_SUBSTR_LEN);
            }
            else
                grc = process_exit_code(FILE_CANNOT_BE_OPENED);
        }
        else
            grc = process_exit_code(INCORRECT_PARAMETERS);
    }
    else
        grc = process_exit_code(INCORRECT_PARAMETERS);

    return grc;
}
