#include "../inc/array_io.h"

int count_integers_in_file(const char *const filename,
size_t *const integer_count)
{
    LOG_INFO("Filename: %s", filename);

    assert(NULL != integer_count);

    int grc = OKAY;

    size_t temp_integer_count = 0;

    FILE *f = fopen(filename, "r");

    if (f)
    {
        int dummy_num;

        while (1 == fscanf(f, "%d", &dummy_num))
            ++temp_integer_count;

        int c;
        if (EOF != (c = fgetc(f)))
        {
            LOG_ERROR("Wrong symbol found in file: %c", c);
            grc = WRONG_SYMBOL_FOUND;
        }

        if (EOF == fclose(f))
        {
            LOG_ERROR("%s", "fclose failed");
            grc = FCLOSE_FAILED;
        }
    }
    else
    {
        LOG_ERROR("Unable to open file %s", filename);
        grc = UNABLE_TO_OPEN_FILE;
    }

    *integer_count = temp_integer_count;
    LOG_INFO("<< integer_count == %zu", *integer_count);
    return grc;
}

int file_to_array(const char *const filename, darray_int_t *const darr)
{
    LOG_INFO(">> Filename %s", filename);
    int rc;

    FILE *f = fopen(filename, "r");

    if (f)
    {
        size_t array_length = darray_length(darr);

        for (size_t i = 0; i < array_length; ++i)
        {
            int temp;
            if (1 != (rc = fscanf(f, "%d", &temp)))
            {
                LOG_ERROR("Expected: %zu; received: %zu", darray_length(darr),
                i + 1);
                return INCORRECT_FILE_NUM_COUNT;
            }

            darray_int_set(darr, i, temp);
        }

        if (EOF == fclose(f))
        {
            LOG_ERROR("fclose failed closing %s", filename);
            return FCLOSE_FAILED;
        }
    }
    else
    {
        LOG_ERROR("Unable to open file %s", filename);
        return UNABLE_TO_OPEN_FILE;
    }

    return OKAY;
}

int array_to_file(const char *const filename, darray_int_t *darr)
{
    FILE *f = fopen(filename, "w");

    if (f)
    {
        size_t array_length = darray_length(darr);

        LOG_DEBUG("Array length == %zu", array_length);
        for (size_t i = 0; i < array_length; ++i)
            fprintf(f, "%d ", darray_int_get(darr, i));

        fprintf(f, "\n");

        if (EOF == fclose(f))
        {
            LOG_ERROR("fclose failed closing %s", filename);
            return FCLOSE_FAILED;
        }
    }
    else
    {
        LOG_ERROR("Unable to open file %s", filename);
        return UNABLE_TO_OPEN_FILE;
    }
    
    return OKAY;
}
