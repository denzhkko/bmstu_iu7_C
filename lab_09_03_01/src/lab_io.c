#include "../inc/lab_io.h"

#define FCLOSE(F, RC) \
if (EOF == fclose(F))    \
{   \
    LOG_ERROR("%s", "Flose failed");    \
    grc = FCLOSE_FAILED;    \
}

int parse_args(int argc, char **argv, args_t *args)
{
    int rc;

    if (ARG_COUNT != argc)
    {
        LOG_ERROR("<< Incorrect arg count = %d", argc);
        return INCORRECT_ARG_COUNT;
    }

    double temp_entered_price;
    rc = sscanf(argv[ARG_PRICE_INDEX], "%lf", &temp_entered_price);

    if (ARG_NUM_INPUT_RC != rc)
    {
        LOG_ERROR("%s", "Arg price not a number");
        return ARG_PRICE_NAN;
    }

    if (temp_entered_price <= 0)
    {
        LOG_ERROR("Notpositive arg price = %lf", temp_entered_price);
        return NOTPOSITIVE_ARG_PRICE;
    }

    args->filename = argv[ARG_FILENAME_INDEX];
    args->entered_price = temp_entered_price;

    LOG_INFO("<< filename = %s; entered_price = %lf",
    args->filename, args->entered_price);

    return OKAY;
}

int process_rc(char *funcname, int rc)
{
    if (!strcmp(funcname, "parse_args"))
        switch (rc)
        {
            case OKAY:
                return ERR_OKAY;
            case INCORRECT_ARG_COUNT:
                return ERR_INCORRECT_ARG_COUNT;
            case ARG_PRICE_NAN:
                return ERR_ARG_PRICE_NAN;
            case NOTPOSITIVE_ARG_PRICE:
                return ERR_NOTPOSITIVE_ARG_PRICE;
            default:
                LOG_ERROR("%s unknown rc = %d", funcname, rc);
                return ERR_UNKNOWN_RC;
        }

    if (!strcmp(funcname, "get_product_vector"))
        switch (rc)
        {
            case OKAY:
                return ERR_OKAY;
            case TITLE_NUM_GET_FAILED:
                return ERR_TITLE_NUM_GET_FAILED;
            case TITLE_NUM_VECTOR_LEN_NE:
                return ERR_TITLE_NUM_VECTOR_LEN_NE;
            case INCORRECT_FILE:
                return ERR_INCORRECT_FILE;
            case FILE_NOT_FOUND:
                return ERR_FILE_NOT_FOUND;
            case FCLOSE_FAILED:
                return ERR_FCLOSE_FAILED;
            case ALLOCATION_FAILED:
                return ERR_ALLOCATION_FAILED;
            case VECTOR_APPEND_FAILED:
                return ERR_VECTOR_APPEND_FAILED;
            default:
                LOG_ERROR("%s unknown rc = %d", funcname, rc);
                return ERR_UNKNOWN_RC;
        }

    if (!strcmp(funcname, "vector_filter"))
        switch (rc)
        {
            case OKAY:
                return ERR_OKAY;
            case REALLOCATION_FAILED:
                return ERR_REALLOCATION_FAILED; // ERR_TARGET_PRODUCT_NOT_EXIST;
            default:
                LOG_ERROR("%s unknown rc = %d", funcname, rc);
                return ERR_UNKNOWN_RC;
        }

    if (!strcmp(funcname, "vector_print"))
        switch (rc)
        {
            case OKAY:
                return ERR_OKAY;
            case TARGET_PRODUCT_NOT_EXIST:
                return ERR_OKAY; // ERR_TARGET_PRODUCT_NOT_EXIST;
            default:
                LOG_ERROR("%s unknown rc = %d", funcname, rc);
                return ERR_UNKNOWN_RC;
        }

    LOG_ERROR("Unknown function %s; rc = %d", funcname, rc);
    return ERR_UNKNOWN_FUNCNAME;
}

int check_curr_char_not_minus(FILE *const f)
{
    int c = getc(f);
    if ('-' == c)
    {
        LOG_ERROR("%s", "<< Negative title num");
        return NEGATIVE_NUM;
    }
    else if (EOF == c)
    {
        LOG_ERROR("%s", "<< Empty line");
        return EOF;
    }
    ungetc(c, f);

    return OKAY;
}

int read_size_t(FILE *const f, size_t *const num)
{
    assert(NULL != f);

    int c, rc;
    size_t temp_num;

    if (OKAY != (rc = check_curr_char_not_minus(f)))
        return rc;

    if (1 != fscanf(f, "%zu", &temp_num))
    {
        LOG_ERROR("%s", "Num getting failed");
        return NUM_GET_FAILED;
    }

    if ('\n' != (c = fgetc(f)) && EOF != c)
    {
        LOG_ERROR("%s", "\'\\n\' or EOF didnt meet after num");
        return INCORRECT_FILE;
    }

    *num = temp_num;

    LOG_INFO("<< Number == %zu", *num);
    return OKAY;
}

int read_product_name(FILE *const f, product_t *const item, char **buffer,
size_t *buffer_len)
{
    ssize_t read = getline(buffer, buffer_len, f);

    assert(!(EOF == read && feof(f) && EINVAL == errno));

    if (EOF == read && feof(f))
    {
        LOG_INFO("%s", "EOF");
        return EOF;
    }
    else if (EOF == read)
    {
        assert(ENOMEM == errno);
        LOG_ERROR("Allocation faled: %s", strerror(errno));
        return ALLOCATION_FAILED;
    }

    size_t str_len = (size_t) ('\n' == (*buffer)[read - 1] ? read - 1 : read);

    if (0 == str_len)
    {
        LOG_ERROR("%s", "String contain only \\n");
        return INCORRECT_FILE;
    }

    char *cutted_str = strndup(*buffer, str_len);

    if (NULL == cutted_str)
    {
        LOG_ERROR("%s", "Allocation for cutted str failed");
        return ALLOCATION_FAILED;
    }

    item->name = cutted_str;

    return OKAY;
}

int read_product(FILE *const f, product_t *const item, char **buffer,
size_t *buffer_len)
{
    assert(NULL != f);
    assert(NULL != item);
    assert(NULL != buffer);
    assert(NULL != buffer_len);

    int rc;
    product_t product;
    product.name = NULL;

    if (OKAY != (rc = read_product_name(f, &product, buffer, buffer_len)))
    {
        LOG_ERROR("read_product_name failed; rc = %d", rc);
        product_item_free(&product);
        return rc;
    }

    if (OKAY != (rc = read_size_t(f, &product.price)))
    {
        product_item_free(&product);
        if (EOF == rc)
        {
            LOG_ERROR("%s", "Unexpected eof");
            return INCORRECT_FILE;
        }
        else
        {
            LOG_ERROR("read_size_t failed; rc = %d", rc);
            return rc;
        }
    }

    *item = product;
    LOG_INFO("Name %s; price %zu", product.name, product.price);
    return OKAY;
}

int read_product_vector_from_file(FILE *f, vector_t *vector)
{
    int rc;
    size_t title_num;

    rc = read_size_t(f, &title_num);

    if (OKAY != rc)
    {
        LOG_ERROR("%s", "Read title num failed");
        return TITLE_NUM_GET_FAILED;
    }

    product_t temp_product;
    
    char *buffer = NULL;
    size_t buffer_len = 0;
    while (OKAY == (rc = read_product(f, &temp_product, &buffer, &buffer_len)))
    {
        rc = vector_append_product(vector, temp_product);

        if (OKAY != rc)
        {
            LOG_ERROR("%s", "Vector append failed");
            return VECTOR_APPEND_FAILED;
        }
        temp_product.name = NULL;
    }
    LOG_INFO("Buffer len at the end: %zu", buffer_len);
    free(buffer);

    if (EOF != rc)
    {
        LOG_ERROR("%s", "Incorrect line");
        return INCORRECT_FILE;
    }
    else if (title_num != vector_get_length(vector))
    {
        LOG_ERROR("Title num = %zu; vector.length = %zu",
        title_num, vector_get_length(vector));

        return TITLE_NUM_VECTOR_LEN_NE;
    }

    return OKAY;
}

int get_product_vector(char *filename, vector_t **vector)
{
    assert(NULL != filename);
    assert(NULL != vector);

    int rc, grc = OKAY;
    FILE *f = NULL;
    *vector = NULL;

    f = fopen(filename, "r");

    if (NULL == f)
    {
        LOG_ERROR("<< File %s not found", filename);
        return FILE_NOT_FOUND;
    }

    *vector = vector_allocate(0, sizeof(product_t));

    if (NULL == *vector)
    {
        LOG_ERROR("%s", "<< Allocation memory for vector zero len failed");

        grc = ALLOCATION_FAILED;
        FCLOSE(f, grc);
        return ALLOCATION_FAILED;
    }

    if (OKAY != (rc = read_product_vector_from_file(f, *vector)))
    {
        product_vector_free(*vector);
        *vector = NULL;

        grc = rc;
        FCLOSE(f, grc);
        return rc;
    }

    FCLOSE(f, grc);

    return grc;
}
