#include "funcs.h"

/**
 * @brief Read title num from file
 *
 * @return OKAY - no error;
 * INCORRECT_LINE - incorrect line;
 * INCORRECT_TITLE_NUM - number out of range;
 * EMPTY_FILE - empty file.
 */
int get_title_num(FILE *const f, int *const title_num)
{
    assert(NULL != f);

    int num;
    if (1 != fscanf(f, "%d", &num))
    {
        if (EOF == fgetc(f))
            return EMPTY_FILE;
        else
            return NOT_FIRST_LINE_NUM;
    }

    if (num < 0)
        return INCORRECT_TITLE_NUM;
    else if (num > MAX_PRODUCT_COUNT)
        return LINE_COUNT_EXCEEDED;

    int c;
    if ('\n' != (c = fgetc(f)) && EOF != c)
        return INCORRECT_TITLE_NUM_ENTRY;

    *title_num = num;
    return OKAY;
}

/**
 * @brief Read line with product data from text file and put it in structure
 *
 * @return OKAY - no error;
 * PRODUCT_NAME_LENGTH_EXCEEDED - length of word exceed;
 * EMPTY_LINE - empty line;
 * INCORRECT_LINE - impossible to read product info from line.
 */
int read_product_line(FILE *const f, s_product *const item)
{
    assert(NULL != f);

    int c;
    s_product product;

    // Read product name
    c = fgetc(f);
    if (EOF == c || '\n' == c)
        return EMPTY_LINE;
    product.name[0] = c;

    for (int i = 1; ; ++i)
    {
        c = fgetc(f);

        if (MAX_NAME_LENGTH  == i && '\n' != c)
            return PRODUCT_NAME_LENGTH_EXCEEDED;
        else if (EOF == c)
            return UNEXPECTED_EOF;
        else if ('\n' == c)
        {
            product.name[i] = '\0';
            break;
        }

        product.name[i] = c;
    }

    // Read product price
    int num;
    
    if (1 != fscanf(f, "%d", &num))
        return INCORRECT_LINE;

    if (num < 0)
        return NEGATIVE_PRODUCT_PRICE;

    if ('\n' != (c = fgetc(f)) && EOF != c)
        return INCORRECT_PRODUCT_PRICE_ENTRY;

    product.price = num;

    *item = product;
    return OKAY;
}

/**
 * @brief read struct from text file to array
 *
 * @return OKAY - no error;
 * INCORRECT_LINE - incorrect line in file;
 * INCORRECT_TITLE_NUM - number out of range;
 * PRODUCT_NAME_LENGTH_EXCEEDED - length of word exceed;
 * MORE_LINES_EXPECTED - more lines expected in file;
 * LESS_LINES_EXPECTED - less lines expected in file;
 * EMPTY_FILE - empty file.
 */
int get_product_array(FILE *const f, s_product *const products,
int *const products_len)
{
    assert(NULL != f);
    assert(NULL != products);

    int rc;

    if (fseek(f, 0L, SEEK_SET))
        return FSEEK_FAILED;

    if (OKAY != (rc = get_title_num(f, products_len)))
        return rc;

    for (int i = 0; i < *products_len; ++i)
    {
        rc = read_product_line(f, products + i);

        if (EMPTY_LINE == rc)
            return MORE_LINES_EXPECTED;
        else if (OKAY != rc)
            return rc;
    }

    s_product item;
    if (EMPTY_LINE != (rc = read_product_line(f, &item)))
        return LESS_LINES_EXPECTED;

    return OKAY;
}

int print_required(const s_product *const products, const int product_count,
const double entered_price)
{
    assert(NULL != products);
    assert(product_count >= 0);
    int is_printed = FALSE;

    for (int i = 0; i < product_count; ++i)
    {
        if (products[i].price < entered_price)
        {
            printf("%s\n%d\n", products[i].name, products[i].price);
            is_printed = TRUE;
        }
    }

    if (FALSE == is_printed)
        return TARGET_PRODUCT_NOT_EXIST;

    return OKAY;
}
