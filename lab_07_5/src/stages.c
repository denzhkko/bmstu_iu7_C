#include "../inc/stages.h"

int process_rc(const char *const funcname, const int return_code)
{
    if (!strcmp(funcname, "stage_input"))
        switch (return_code)
        {
            case OKAY:
                return ERR_OKAY;
            case COUNTING_INTS_FAILED:
                return ERR_COUNTING_INTS_FAILED;
            case ZERO_SRC_ARRAY_LEN:
                return ERR_ZERO_SRC_ARRAY_LEN;
            case ARRAY_ALLOCATION_FAILED:
                return ERR_ARRAY_ALLOCATION_FAILED;
            case READ_INTS_FROM_FILE_FAILED:
                return ERR_READ_INTS_FROM_FILE_FAILED;
            default:
                LOG_ERROR("%s unknown rc = %d", funcname, return_code);
                return ERR_UNKNOWN_RC;
        }

    if (!strcmp(funcname, "stage_process"))
        switch (return_code)
        {
            case OKAY:
                return ERR_OKAY;
            case INCORRECT_ARRAY_FOR_FILTER:
                return ERR_INCORRECT_ARRAY_FOR_FILTER;
            case FILTER_ARRAY_FAILED:
                return ERR_FILTER_ARRAY_FAILED;
            default:
                LOG_ERROR("%s unknown rc = %d", funcname, return_code);
                return ERR_UNKNOWN_RC;
        }

    if (!strcmp(funcname, "stage_output"))
        switch (return_code)
        {
            case OKAY:
                return ERR_OKAY;
            case WRITING_ARRAY_FAILED:
                return ERR_WRITING_ARRAY_FAILED;
            default:
                LOG_ERROR("%s unknown rc = %d", funcname, return_code);
                return ERR_UNKNOWN_RC;
        }

    LOG_ERROR("Unknown function %s; rc = %d", funcname, return_code);
    return ERR_UNKNOWN_FUNC_NAME;
}

int stage_input(char *filename_in, darray_int_t **darr)
{
    int rc, grc = OKAY;

    size_t int_count = 0;
    rc = count_integers_in_file(filename_in, &int_count);

    if (OKAY != rc)
    {
        grc = COUNTING_INTS_FAILED;
        goto fin;
    }
    else if (0 == int_count)
    {
        grc = ZERO_SRC_ARRAY_LEN;
        goto fin;
    }

    rc = darray_int_init(darr, int_count);

    if (OKAY != rc)
    {
        LOG_ERROR("%s", "Array allocation failed");
        grc = ARRAY_ALLOCATION_FAILED;
        goto fin;
    }

    rc = file_to_array(filename_in, *darr);

    if (OKAY != rc)
    {
        grc = READ_INTS_FROM_FILE_FAILED;
        goto free_darr;
    }

    goto fin;

free_darr: // ONLY IF ERROR
    darray_int_free(*darr);

fin:
    return grc;
}

int stage_process(darray_int_t *darr, bool need_filter)
{
    int rc, grc = OKAY;

    int *darr_data_ptr = darray_get_data_ptr(darr);
    size_t darr_len = darray_length(darr);

    if (need_filter)
    {
        int *pb_dst, *pe_dst;
        rc = key(darr_data_ptr, darr_data_ptr + darr_len, &pb_dst, &pe_dst);

        if (OKAY == rc)
        {
            darray_set_length(darr, (size_t)  (pe_dst - pb_dst));
            darray_set_data_ptr(darr, pb_dst);

            darr_len = darray_length(darr);
            darr_data_ptr = darray_get_data_ptr(darr);

            LOG_INFO("Filtered array len %zu", darr_len);
        }
        else
        {
            LOG_ERROR("%s", "Key function return erorr");
            grc = FILTER_ARRAY_FAILED;
            goto fin;
        }
    }

    mysort(darr_data_ptr, darr_len, sizeof(int), *compare_int);

fin:
    return grc;
}

int stage_output(darray_int_t *darr, char *filename_out)
{
    int rc, grc = OKAY;

    rc = array_to_file(filename_out, darr);

    if (OKAY != rc)
    {
        grc = WRITING_ARRAY_FAILED;
    }

    LOG_DEBUG("%s", "After stage output");
    return grc;
}
