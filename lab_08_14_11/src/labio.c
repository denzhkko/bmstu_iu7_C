#include "../inc/labio.h"

int parse_args(int argc, char **argv, args_t *args)
{
    if (5 == argc && !strcmp("a", argv[ACTION_INDEX]))
    {
        args->action = 'a';
        args->fm_filename = argv[FM_FILENAME_INDEX];
        args->sm_filename = argv[SM_FILENAME_INDEX];
        args->out_filename = argv[OUT_FILENAME_INDEX];

        LOG_INFO("<< action = %c; fm_filename = %s; ",
        args->action, args->fm_filename);
        LOG_INFO("<< sm_filename = %s; ""out_filename = %s",
        args->sm_filename, args->out_filename);

        return OKAY;
    }
    else if (5 == argc && !strcmp("m", argv[ACTION_INDEX]))
    {
        args->action = 'm';
        args->fm_filename = argv[FM_FILENAME_INDEX];
        args->sm_filename = argv[SM_FILENAME_INDEX];
        args->out_filename = argv[OUT_FILENAME_INDEX];

        LOG_INFO("<< action = %c; fm_filename = %s; ",
        args->action, args->fm_filename);
        LOG_INFO("<< sm_filename = %s; ""out_filename = %s",
        args->sm_filename, args->out_filename);

        return OKAY;
    }
    else if (4 == argc && !strcmp("o", argv[ACTION_INDEX]))
    {
        args->action = 'o';
        args->fm_filename = argv[FM_FILENAME_INDEX];
        args->sm_filename = NULL;
        args->out_filename = argv[OUT_FILENAME_INDEX - 1];

        LOG_INFO("<< action = %c; fm_filename = %s; ",
        args->action, args->fm_filename);
        LOG_INFO("<< sm_filename = %s; ""out_filename = %s",
        args->sm_filename, args->out_filename);

        return OKAY;
    }
    else
    {
        return INCORRECT_ARGS;
    }
}

int process_rc(const int return_code)
{
    switch (return_code)
    {
        case OKAY:
            LOG_INFO("%s", "<< grc = ERR_OKAY");
            return ERR_OKAY;
        case MENU_CASE_SUM_FAILED:
            LOG_ERROR("%s", "<< grc = ERR_MENU_CASE_SUM_FAILED");
            return ERR_MENU_CASE_SUM_FAILED;
        case MENU_CASE_MULTIPLE_FAILED:
            LOG_ERROR("%s", "<< grc = ERR_MENU_CASE_MULTIPLE_FAILED");
            return ERR_MENU_CASE_MULTIPLE_FAILED;
        case MENU_CASE_INVERT_FAILED:
            LOG_ERROR("%s", "<< grc = ERR_MENU_CASE_INVERT_FAILED");
            return ERR_MENU_CASE_INVERT_FAILED;
        case NEVER_GET_HERE:
            LOG_ERROR("%s", "<< grc = ERR_NEVER_GET_HERE");
            return ERR_NEVER_GET_HERE;
        default:
            LOG_ERROR("%s", "<< grc = ERR_UNKNOWN");
            return ERR_UNKNOWN;
    }
}
