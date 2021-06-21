#include <stdio.h>

#include "matrix_method.h"

#define FILENAME_IN "in.txt"
#define FILENAME_OUT "out.txt"

#define OKAY_ERROR                      0
#define NOT_OKAY_ERROR                  1

int main(void)
{
    int rc;

    matrix_t matrix;
    rc = file_to_matrix(FILENAME_IN, &matrix);
    if (OKAY != rc)
    {
        saper(&matrix);

        rc = delete_rows(&matrix);
        if (OKAY != rc)
        {
            LOG_ERROR("%s", "delete_rows failed");
            return NOT_OKAY_ERROR;
            matrix_free(&matrix);
        }

        rc = matrix_to_file(FILENAME_OUT, &matrix);
        if (OKAY != rc)
        {
            LOG_ERROR("%s", "matrix_to_file failed");
            matrix_free(&matrix);
            return NOT_OKAY_ERROR;
        }

        matrix_free(&matrix);
    }
    else
    {
        LOG_ERROR("%s", "file_to_matrix failed");
        return NOT_OKAY_ERROR;
    }

}
