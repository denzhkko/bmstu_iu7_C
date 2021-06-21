#include "check_cmp.h"

int is_fptr_double_matrix_eq(FILE *ff, FILE *sf)
{
    int rc;
    int fn, fm, sn, sm;
    rc = fscanf(ff, "%d%d", &fn, &fm);

    if (2 != rc)
    {
        LOG_ERROR("from %s scaned only %d first numbers", f_filename, rc);
        return INCORRECT_FILE;
    }

    rc = fscanf(sf, "%d%d", &sn, &sm);

    if (2 != rc)
    {
        LOG_ERROR("from %s scaned only %d first numbers", s_filename, rc);
        return INCORRECT_FILE;
    }

    if (fn != sn || fm != sm)
    {
        LOG_ERROR("Matrix size is not equal %dx%d vs %dx%d", fn, fm, sn, sm);
        return FILE_NOT_EQUAL;
    }

    if (0 >= fn || 0 >= fm)
    {
        LOG_ERROR("Not positive size value: %d or %d", fn, fm);
        return INCORRECT_FILE;
    }

    for (size_t i = 0; i < (size_t) fn * (size_t) fm; ++i)
    {
        double f_value, s_value;

        rc = fscanf(ff, "%lf", &f_value);

        if (1 != rc)
        {
            LOG_ERROR("Unable to read matrix value from %s", f_filename);
            return INCORRECT_FILE;
        }

        rc = fscanf(sf, "%lf", &s_value);

        if (1 != rc)
        {
            LOG_ERROR("Unable to read matrix value from %s", s_filename);
            return INCORRECT_FILE;
        }

        if (fabs(f_value - s_value) >= DOUBLE_TOL)
        {
            LOG_ERROR("value [%zu; %zu] is not equal; %lf vs %lf",
            i / (size_t) fm, (size_t) i % (size_t) fm, f_value, s_value);

            return FILE_NOT_EQUAL;
        }
    }

    return FILE_EQUAL;
}

int is_file_double_matrix_eq(char *f_filename, char *s_filename)
{
    LOG_INFO(">> ffn = %s; sfn = %s", f_filename, s_filename);
    int grc;

    FILE *ff = fopen(f_filename, "r");

    if (NULL != ff)
    {
        FILE *sf = fopen(s_filename, "r");

        if (NULL != sf)
        {
            grc = is_fptr_double_matrix_eq(ff, sf);

            if (EOF == fclose(sf))
            {
                LOG_ERROR("fclose %s failed", s_filename);
                grc = FCLOSE_FAILED;
            }
        }
        else
        {
            LOG_ERROR("Unable to open file %s", s_filename);
            grc = FILE_CANNOT_BE_OPENED;
        }

        if (EOF == fclose(ff))
        {
            LOG_ERROR("fclose %s failed", f_filename);
            grc = FCLOSE_FAILED;
        }
    }
    else
    {
        LOG_ERROR("Unable to open file %s", f_filename);
        grc = FILE_CANNOT_BE_OPENED;
    }

    LOG_DEBUG("grc = %d", grc);
    return grc;
}
