#include <stdio.h>
#include <string.h>

#include "../inc/lab_io.h"
#include "../inc/errors.h"

int main(int argc, char **argv)
{
    int rc;
    args_t args;
    vector_t *vector;

    if (OKAY != (rc = parse_args(argc, argv, &args)))
    {
        LOG_ERROR("%s", "Parsing failed");
        return process_rc("parse_args", rc);
    }

    if (OKAY != (rc = get_product_vector(args.filename, &vector)))
    {
        LOG_ERROR("%s", "get_product_vector failed");
        return process_rc("get_product_vector", rc);
    }

    if (OKAY != (rc = vector_filter(vector, args.entered_price)))
    {
        LOG_ERROR("%s", "vector_filter failed");
        product_vector_free(vector);
        return process_rc("vector_filter", rc);
    }

    vector_print(vector);

    product_vector_free(vector);

    return ERR_OKAY;
}
