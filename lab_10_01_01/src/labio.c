#include "../inc/labio.h"

int parce_args(int argc, char **argv, args_t *args)
{
    if (ARGS_COUNT != argc)
    {
        LOG_ERROR("<< Incorrect args count: %d", argc);
        return INCORRECT_ARGS_COUNT;
    }

    args->filename_in = argv[FILENAME_IN_INDEX];
    args->filename_out_f = argv[FILENAME_OUT_F_INDEX];
    args->filename_out_s = argv[FILENAME_OUT_S_INDEX];

    LOG_INFO("<< filename_in = %s; filename_out_f = %s; filename_out_s = %s",
    args->filename_in, args->filename_out_f, args->filename_out_s);

    return OKAY;
}
