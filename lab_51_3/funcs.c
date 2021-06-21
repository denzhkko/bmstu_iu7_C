#include "funcs.h"

int fill_file(FILE *f, const size_t num_count)
{
    assert(NULL != f);
    assert(num_count >= 0);

    srand(time(NULL));

    int32_t num;
    int num_size = sizeof(num);

    for (size_t i = 0; i < num_count; ++i)
    {
        num = rand() - rand();

        if (1 != fwrite(&num, num_size, 1, f))
            return FWRITE_FAILED;
    }

    return OKAY;
}

int get_file_size(FILE *f, size_t *const size)
{
    assert(NULL != f);

    if (fseek(f, 0L, SEEK_END))
        return FSEEK_FAILED;

    size_t sz = ftell(f);    
    if (sz < 0)
        return FTELL_FAILED;

    *size = sz;
    
    if (fseek(f, 0L, SEEK_SET))
        return FSEEK_FAILED;

    return OKAY;
}

int print_file(FILE *f)
{
    assert(NULL != f);

    int rc;
    int32_t num;
    int num_size = sizeof(num);

    size_t file_size;

    rc = get_file_size(f, &file_size);

    if (OKAY == rc)
    {
        if (0 == file_size)
            return EMPTY_FILE;

        if (file_size % num_size)
            return INCORRECT_FILE_SIZE;

        size_t num_count = file_size / num_size;

        for (size_t i = 0; i < num_count; ++i)
        {
            if (1 != fread(&num, num_size, 1, f))
                return FREAD_FAILED;

            printf("%"PRId32" ", num);
        }
        printf("\n");
        return OKAY;
    }
    else
        return rc;
}

int32_t get_number_by_pos(FILE *f, const size_t pos)
{
    assert(NULL != f);
    assert(pos >= 0);

    int rc;

    rc = fseek(f, pos * sizeof(int32_t), SEEK_SET);

    assert(0 == rc);

    int32_t num;
    
    rc = fread(&num, sizeof(num), 1, f);

    assert(1 == rc);

    return num;
}

void put_number_by_pos(FILE *f, const size_t pos, const int32_t num)
{
    assert(NULL != f);
    assert(pos >= 0);

    int rc;

    rc = fseek(f, pos * sizeof(num), SEEK_SET);

    assert(0 == rc);

    rc = fwrite(&num, sizeof(num), 1, f);

    assert(1 == rc);
}

int sort_file(FILE *f)
{
    assert(NULL != f);

    size_t file_size;
    int rc;

    rc = get_file_size(f, &file_size);

    if (rc == OKAY)
    {
        if (0 == file_size)
            return EMPTY_FILE;

        if (file_size % sizeof(int32_t))
            return INCORRECT_FILE_SIZE;

        size_t num_count = file_size / sizeof(int32_t);

        for (size_t i = num_count; i > 0; --i)
            for (size_t j = 0; j < i - 1; ++j)
                if (get_number_by_pos(f, j) > get_number_by_pos(f, j + 1))
                {
                    int32_t k = get_number_by_pos(f, j);
                    put_number_by_pos(f, j, get_number_by_pos(f, j + 1));
                    put_number_by_pos(f, j + 1, k);
                }
        return OKAY;
    }
    else
        return rc;
}

int process_exit_code(const int exit_code)
{
    switch (exit_code)
    {
        case OKAY:
            return OKAY;
        case INCORRECT_COMMAND:
            fprintf(stderr, INCORRECT_COMMAND_MESS);
            return INCORRECT_COMMAND_ERROR;
        case INCORRECT_START:
            fprintf(stderr, INCORRECT_START_MESS);
            return INCORRECT_START_ERROR;
        case FILE_CANNOT_BE_OPENED:
            perror("");
            return FILE_CANNOT_BE_OPENED_ERROR;
        case FCLOSE_FAILED:
            perror("");
            return FCLOSE_FAILED_ERROR;
        case FWRITE_FAILED:
            perror("fwrite failed");
            return FWRITE_FAILED_ERROR;
        case FSEEK_FAILED:
            fprintf(stderr, FSEEK_FAILED_MESS);
            return FSEEK_FAILED_ERROR;
        case FTELL_FAILED:
            fprintf(stderr, FTELL_FAILED_MESS);
            return FTELL_FAILED_ERROR;
        case FREAD_FAILED:
            fprintf(stderr, FREAD_FAILED_MESS);
            return FREAD_FAILED_ERROR;
        case EMPTY_FILE:
            fprintf(stderr, EMPTY_FILE_MESS);
            return EMPTY_FILE_ERROR;
        case INCORRECT_FILE_SIZE:
            fprintf(stderr, INCORRECT_FILE_SIZE_MESS);
            return INCORRECT_FILE_SIZE_ERROR;
        default:
            fprintf(stderr, UNKNOWN_EXIT_CODE_MESS);
            return UNKNOWN_EXIT_CODE_ERROR;
    }
}
