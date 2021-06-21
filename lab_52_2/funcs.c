#include <stdio.h>

#include "funcs.h"

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

struct product get_item_by_pos(FILE *f, const size_t pos)
{
    assert(NULL != f);
    assert(pos >= 0);

    int rc;

    rc = fseek(f, pos * sizeof(struct product), SEEK_SET);

    assert(0 == rc);

    struct product item;

    rc = fread(&item, sizeof(item), 1, f);

    assert(1 == rc);

    return item;
}

void put_item_by_pos(FILE *f, const size_t pos,
const struct product item)
{
    assert(NULL != f);
    assert(pos >= 0);

    int rc;

    rc = fseek(f, pos * sizeof(item), SEEK_SET);

    assert(0 == rc);

    rc = fwrite(&item, sizeof(item), 1, f);

    assert(1 == rc);
}


int sort_file(FILE *f_in, FILE *f_out)
{
    assert(NULL != f_in);
    assert(NULL != f_out);

    int rc;
    size_t file_size;

    if (OKAY != (rc = get_file_size(f_in, &file_size)))
        return rc;

    if (0 == file_size)
        return EMPTY_FILE;

    if (file_size % sizeof(struct product))
        return INCORRECT_FILE_SIZE;

    size_t item_count = file_size / sizeof(struct product);

    for (size_t i = 0; i < item_count; ++i)
    {
        struct product item = get_item_by_pos(f_in, i);
        put_item_by_pos(f_out, i, item);
    }

    for (size_t i = item_count; i > 0; --i)
        for (size_t j = 0; j < i - 1; ++j)
        {
            struct product item1 = get_item_by_pos(f_out, j);
            struct product item2 = get_item_by_pos(f_out, j + 1);

            int is_swap_it = (item1.price < item2.price ||
                (item1.price == item2.price && item1.quantity < item2.quantity));

            if (is_swap_it)
            {
                struct product k = get_item_by_pos(f_out, j);
                put_item_by_pos(f_out, j, get_item_by_pos(f_out, j + 1));
                put_item_by_pos(f_out, j + 1, k);
            }
        }

    return OKAY;
}

int is_substr_at_end(char *str, char *substr)
{
    size_t str_len = strlen(str);
    size_t substr_len = strlen(substr);

    if (substr_len > str_len)
        return FALSE;

    if (0 == strcmp(substr, str + str_len - substr_len))
        return TRUE;

    return FALSE;
}

int find_items(FILE *f, char *substr)
{
    assert(NULL != f);

    int rc;
    size_t file_size;
    size_t correct_count = 0;

    if (OKAY != (rc = get_file_size(f, &file_size)))
        return rc;

    if (0 == file_size)
        return EMPTY_FILE;

    if (file_size % sizeof(struct product))
        return INCORRECT_FILE_SIZE;

    size_t item_count = file_size / sizeof(struct product);

    for (size_t i = 0; i < item_count; ++i)
    {
        struct product item = get_item_by_pos(f, i);

        if (is_substr_at_end(item.name, substr))
        {
            printf("%s\n%s\n", item.name, item.producer);
            printf("%"PRIu32"\n%"PRIu32"\n", item.price, item.quantity);
            ++correct_count;
        }
    }

    if (0 == correct_count)
        return NO_MATCHING_ITEMS;

    return OKAY;
}

int is_file_sorted(FILE *f)
{
    assert(NULL != f);

    int rc;
    size_t file_size;

    if (OKAY != (rc = get_file_size(f, &file_size)))
        return rc;

    if (file_size % sizeof(struct product))
        return INCORRECT_FILE_SIZE;

    size_t item_count = file_size / sizeof(struct product);

    for (size_t i = 0; i + 1 < item_count; ++i)
    {
        struct product item1 = get_item_by_pos(f, i);
        struct product item2 = get_item_by_pos(f, i + 1);

        int is_correct = !(item1.price < item2.price ||
            (item1.price == item2.price && item1.quantity < item2.quantity));

        if (!is_correct)
            return FALSE;
    }

    return TRUE;
}

int append_to_sorted_file(FILE *f)
{
    assert(NULL != f);

    int rc;
    size_t file_size;

    if (OKAY != (rc = get_file_size(f, &file_size)))
        return rc;

    if (file_size % sizeof(struct product))
        return INCORRECT_FILE_SIZE;

    size_t item_count = file_size / sizeof(struct product);

    if (!is_file_sorted(f))
        return FILE_ISNOT_SORTED;

    struct product item;
    memset(&item, 0, sizeof(struct product));

    for (int i = 0; i < MAX_NAME_LEN + 1; ++i)
        item.name[i] = '\0';

    for (int i = 0; i < MAX_PRODUCER_LEN + 1; ++i)
        item.producer[i] = '\0';

    if (1 != scanf("%30s", item.name))
        return INCORRECT_PRODUCT_FIELD;

    if (1 != scanf("%15s", item.producer))
        return INCORRECT_PRODUCT_FIELD;

    if (1 != scanf("%"SCNu32"", &(item.price)))
        return INCORRECT_PRODUCT_FIELD;

    if (1 != scanf("%"SCNu32"", &(item.quantity)))
        return INCORRECT_PRODUCT_FIELD;

    char check_char;
    if (1 == (rc = scanf("%c", &check_char)) && (check_char != '\n'))
    {
        printf("$%c$", check_char);
        return INCORRECT_PRODUCT_FIELD;
    }

    size_t insert_index;
    for (insert_index = 0; insert_index + 1 <= item_count; ++insert_index)
    {
        struct product f_item = get_item_by_pos(f, insert_index);

        int is_less = (f_item.price < item.price ||
            (f_item.price == item.price && f_item.quantity < item.quantity));

        if (is_less)
            break;
    }

    for (size_t i = item_count; i > insert_index; --i)
        put_item_by_pos(f, i, get_item_by_pos(f, i - 1));

    put_item_by_pos(f, insert_index, item);

    return OKAY;
}

int process_exit_code(const int exit_code)
{
    switch (exit_code)
    {
        case OKAY:
            return OKAY;
        case FILE_CANNOT_BE_OPENED:
            perror("");
            return FILE_CANNOT_BE_OPENED;
        case FSEEK_FAILED:
            fprintf(stderr, FSEEK_FAILED_MESS);
            return FSEEK_FAILED_ERROR;
        case FTELL_FAILED:
            fprintf(stderr, FTELL_FAILED_MESS);
            return FTELL_FAILED_ERROR;
        case EMPTY_FILE:
            fprintf(stderr, EMPTY_FILE_MESS);
            return EMPTY_FILE_ERROR;
        case INCORRECT_FILE_SIZE:
            fprintf(stderr, INCORRECT_FILE_SIZE_MESS);
            return INCORRECT_FILE_SIZE_ERROR;
        case FCLOSE_FAILED:
            perror("");
            return FCLOSE_FAILED_ERROR;
        case INCORRECT_SUBSTR_LEN:
            fprintf(stderr, INCORRECT_SUBSTR_LEN_MESS);
            return INCORRECT_SUBSTR_LEN_ERROR;
        case NO_MATCHING_ITEMS:
            // fprintf(stderr, NO_MATCHING_ITEMS_MESS);
            return NO_MATCHING_ITEMS_ERROR;
        case INCORRECT_PRODUCT_FIELD:
            fprintf(stderr, INCORRECT_PRODUCT_FIELD_MESS);
            return INCORRECT_PRODUCT_FIELD_ERROR;
        case FILE_ISNOT_SORTED:
            fprintf(stderr, FILE_ISNOT_SORTED_MESS);
            return FILE_ISNOT_SORTED_ERROR;
        case INCORRECT_PARAMETERS:
            fprintf(stderr, INCORRECT_PARAMETERS_MESS);
            return INCORRECT_PARAMETERS_ERROR;
        default:
            fprintf(stderr, UNKNOWN_EXIT_CODE_MESS);
            return UNKNOWN_EXIT_CODE_ERROR;
    }
}
