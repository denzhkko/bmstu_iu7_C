#include <stdio.h>
#include <string.h>

#include "funcs.h"

#define MAX_FILENAME_LEN 30

#define MAX_FILENAME_LEN_EXCEEDED 123

#define ERR_OKAY                            0
#define ERR_INCORRECT_ARGS                  1
#define ERR_NONEXITSTENT_FILE               2
#define ERR_NOT_POSIVITE_ARG_PRICE          3
#define ERR_EMPTY_FILE                      4
#define ERR_LINE_COUNT_EXCEEDED             5
#define ERR_MORE_LINES_EXPECTED             6
#define ERR_LESS_LINES_EXPECTED             7
#define ERR_PRODUCT_NAME_LENGTH_EXCEEDED    8
#define ERR_NEGATIVE_PRODUCT_PRICE          9
#define ERR_INCORRECT_LINE                  11
#define ERR_TARGET_PRODUCT_NOT_EXIST        12
#define ERR_INCORRECT_TITLE_NUM             14
#define ERR_NOT_NUMBER_IN_ARGS              15
#define ERR_NOT_FIRST_LINE_NUM              16
#define ERR_UNEXPECTED_EOF                  17
#define ERR_INCORRECT_TITLE_NUM_ENTRY       18
#define ERR_INCORRECT_PRODUCT_PRICE_ENTRY   19
#define ERR_MAX_FILENAME_LEN_EXCEEDED       123
#define ERR_FCLOSE_FAILED                   124
#define ERR_FSEEK_FAILED                    125
#define ERR_UNKNOWN_ERROR                   127

#define ARGS_NUM 3
#define ARG_NUM_IMPUT_RC 1

int process_exit_code(const int exit_code)
{
    switch (exit_code)
    {
        case OKAY:
            return ERR_OKAY;
        case INCORRECT_ARGS:
            return ERR_INCORRECT_ARGS;
        case NONEXITSTENT_FILE:
            return ERR_NONEXITSTENT_FILE;
        case NOT_POSIVITE_ARG_PRICE:
            return ERR_NOT_POSIVITE_ARG_PRICE;
        case EMPTY_FILE:
            return ERR_EMPTY_FILE;
        case LINE_COUNT_EXCEEDED:
            return LINE_COUNT_EXCEEDED;
        case MORE_LINES_EXPECTED:
            return MORE_LINES_EXPECTED;
        case LESS_LINES_EXPECTED:
            return ERR_LESS_LINES_EXPECTED;
        case PRODUCT_NAME_LENGTH_EXCEEDED:
            return ERR_PRODUCT_NAME_LENGTH_EXCEEDED;
        case NEGATIVE_PRODUCT_PRICE:
            return ERR_NEGATIVE_PRODUCT_PRICE;
        case INCORRECT_LINE:
            return ERR_INCORRECT_LINE;
        case TARGET_PRODUCT_NOT_EXIST:
            return ERR_OKAY; // ERR_TARGET_PRODUCT_NOT_EXIST;
        case INCORRECT_TITLE_NUM:
            return ERR_INCORRECT_TITLE_NUM;
        case NOT_NUMBER_IN_ARGS:
            return ERR_NOT_NUMBER_IN_ARGS;
        case NOT_FIRST_LINE_NUM:
            return ERR_NOT_FIRST_LINE_NUM;
        case UNEXPECTED_EOF:
            return ERR_UNEXPECTED_EOF;
        case INCORRECT_TITLE_NUM_ENTRY:
            return ERR_INCORRECT_TITLE_NUM_ENTRY;
        case ERR_INCORRECT_PRODUCT_PRICE_ENTRY:
            return ERR_INCORRECT_PRODUCT_PRICE_ENTRY;
        case MAX_FILENAME_LEN_EXCEEDED:
            return ERR_MAX_FILENAME_LEN_EXCEEDED;
        case FCLOSE_FAILED:
            return ERR_FCLOSE_FAILED;
        case FSEEK_FAILED:
            return ERR_FSEEK_FAILED;
        default:
            return ERR_UNKNOWN_ERROR;
    }
}

int parse_args(const int argc, const char **argv, char *filename,
double *entered_price)
{
    int rc;

    if (ARGS_NUM != argc)
        return INCORRECT_ARGS;

    double temp_entered_price;
    if (ARG_NUM_IMPUT_RC != (rc = sscanf(argv[2], "%lf", &temp_entered_price)))
        return NOT_NUMBER_IN_ARGS;

    if (temp_entered_price <= 0)
        return NOT_POSIVITE_ARG_PRICE;

    if (strlen(argv[1]) > MAX_FILENAME_LEN)
        return MAX_FILENAME_LEN_EXCEEDED;

    strncpy(filename, argv[1], MAX_FILENAME_LEN + 1);
    
    *entered_price = temp_entered_price;

    return OKAY;
}

int main(const int argc, const char **argv)
{
    int rc;
    char filename[MAX_FILENAME_LEN + 1];
    double entered_price;

    if (OKAY != (rc = parse_args(argc, argv, filename, &entered_price)))
        return process_exit_code(rc);
    
    FILE *f;
    if (!(f = fopen(filename, "r")))
        return process_exit_code(NONEXITSTENT_FILE);

    int product_count;
    s_product products[MAX_PRODUCT_COUNT];
    rc = get_product_array(f, products, &product_count);

    if (EOF == fclose(f))
        return process_exit_code(FCLOSE_FAILED);

    if (OKAY != rc)
        return process_exit_code(rc);

    if (OKAY != (rc = print_required(products, product_count, entered_price)))
        return process_exit_code(rc);

    return process_exit_code(OKAY);
}
