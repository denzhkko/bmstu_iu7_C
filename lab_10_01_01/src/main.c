#include <stdio.h>

#include "../inc/errors.h"
#include "../inc/macrologger.h"

#include "../inc/labio.h"
#include "../inc/stages.h"

int main(int argc, char **argv)
{
    int rc, grc;
    args_t args;

    rc = parce_args(argc, argv, &args);

    if (OKAY != rc)
    {
        LOG_ERROR("Parce args failed; rc = %d", rc);
        return ERR_INCORRECT_ARGS;
    }

    grc = run_stages(&args);

    return grc;
}
