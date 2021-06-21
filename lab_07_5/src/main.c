#include <stdio.h>
#include <stdbool.h>

#include "../inc/lab_07_io.h"
#include "../inc/stages.h"

int main(const int argc, char **argv)
{
    int rc, grc = OKAY;
    args_fileds_t args;

    rc = parce_args(argc, argv, &args);

    if (OKAY != rc)
        return rc;

    darray_int_t *darr = NULL;

    if (OKAY != (rc = stage_input(args.filename_in, &darr)))
    {
        grc = process_rc("stage_input", rc);
        goto fin;
    }

    if (OKAY != (rc = stage_process(darr, args.need_filter)))
    {
        grc = process_rc("stage_process", rc);
        goto free_darr;
    }

    if (OKAY != (rc = stage_output(darr, args.filename_out)))
    {
        grc = process_rc("stage_output", rc);
        goto free_darr;
    }

    free_darr:
        darray_int_free(darr);
    fin:
        return grc;
}
