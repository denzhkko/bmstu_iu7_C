#include <stdio.h>

#include "../inc/macrologger.h"
#include "../inc/errors.h"

#include "../inc/labio.h"
#include "../inc/matrix_methods.h"
#include "../inc/menu.h"

int main(int argc, char **argv)
{
    int rc, grc = ERR_OKAY;

    args_t args;
    rc = parse_args(argc, argv, &args);

    if (OKAY != rc)
    {
        grc = ERR_INCORRECT_ARGS;
        LOG_INFO("%s", "<< grc = ERR_INCORRECT_ARGS");
        return grc;
    }

    rc = menu(&args);

    if (OKAY != rc)
    {
        LOG_ERROR("%s", "Menu failed");
        grc = rc;
    }

    return process_rc(grc);
}
