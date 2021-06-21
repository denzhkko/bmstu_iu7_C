#include "../inc/lab_07_io.h"

int parce_args(const int argc, char **argv, args_fileds_t *data)
{
    if (3 != argc && 4 != argc)
    {
        LOG_ERROR("argc == %d", argc);
        return INCORRECT_ARG_COUNT;
    }

    data->filename_in = (char *) *(argv + FILENAME_IN_INDEX);

    data->filename_out = (char *) *(argv  + FILENAME_OUT_INDEX);

    if (4 == argc)
    {
        if (strcmp("f", *(argv + FILTER_INDEX)))
        {
            LOG_ERROR("Incorrect filter key: %s", *(argv + FILTER_INDEX));
            return INCORRECT_FILTER_KEY;
        }

        data->need_filter = true;
    }
    else // 3 == argc
    {
        data->need_filter = false;
    }

    LOG_INFO("<< filename_in == %s, filename_out == %s, need_format == %d",
    data->filename_in, data->filename_out, data->need_filter);

    return OKAY;
}
