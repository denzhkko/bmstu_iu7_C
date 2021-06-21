/* Type: int32_t
 * Algorithm: bobble sort
 * Orientation: increase
 */

#include <stdio.h>
#include <string.h>

#include "funcs.h"

int main(int argc, char **argv)
{
    FILE *f;
    int rc;
    int grc = OKAY;

    if (3 == argc)
    {
        if (0 == strcmp(argv[1], "c"))
        {
            f = fopen(argv[2], "wb");

            if (f)
            {
                size_t num_count = 9;

                if (OKAY != (rc = fill_file(f, num_count)))
                    grc = process_exit_code(rc);

                if (EOF == fclose(f))
                    grc = process_exit_code(FCLOSE_FAILED);
            }
            else
            {
                grc = process_exit_code(FILE_CANNOT_BE_OPENED);
            }
        }
        else if (0 == strcmp(argv[1], "p"))
        {
            f = fopen(argv[2], "rb");

            if (f)
            {
                if (OKAY != (rc = print_file(f)))
                    grc = process_exit_code(rc);

                if (EOF == fclose(f))
                    grc = process_exit_code(FCLOSE_FAILED);
            }
            else
            {
                grc = process_exit_code(FILE_CANNOT_BE_OPENED);
            }
        }
        else if (0 == strcmp(argv[1], "s"))
        {
            f = fopen(argv[2], "rb+");

            if (f)
            {
                if (OKAY != (rc = sort_file(f)))
                    grc = process_exit_code(rc);

                if (EOF == fclose(f))
                    grc = process_exit_code(FCLOSE_FAILED);
            }
            else
            {
                grc = process_exit_code(FILE_CANNOT_BE_OPENED);
            }
        }
        else
        {
            grc = process_exit_code(INCORRECT_COMMAND_ERROR);
        }
    }
    else
    {
        grc = process_exit_code(INCORRECT_START);
    }
    
    return grc;
}
