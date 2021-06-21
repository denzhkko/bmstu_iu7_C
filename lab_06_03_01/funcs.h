#ifndef _FUNCS_H_
#define _FUNCS_H_

#include <stdio.h>
#include <assert.h>

#define OKAY 0
#define INCORRECT_ARGS 1
#define NONEXITSTENT_FILE 2
#define NOT_POSIVITE_ARG_PRICE 3
#define EMPTY_FILE 4
#define LINE_COUNT_EXCEEDED 5
#define MORE_LINES_EXPECTED 6
#define LESS_LINES_EXPECTED 7
#define PRODUCT_NAME_LENGTH_EXCEEDED 8
#define NEGATIVE_PRODUCT_PRICE 9
#define INCORRECT_LINE 11
#define TARGET_PRODUCT_NOT_EXIST 12
#define INCORRECT_TITLE_NUM 14
#define NOT_NUMBER_IN_ARGS 15
#define NOT_FIRST_LINE_NUM 16
#define UNEXPECTED_EOF 17
#define INCORRECT_TITLE_NUM_ENTRY 18
#define INCORRECT_PRODUCT_PRICE_ENTRY 19
#define FCLOSE_FAILED 124
#define FSEEK_FAILED 125
#define EMPTY_LINE 126

#define MAX_NAME_LENGTH 25
#define MAX_PRODUCT_COUNT 15

#define TRUE 1
#define FALSE 0

typedef struct product s_product;

struct product
{
    char name[MAX_NAME_LENGTH + 1];
    int price;
};

int get_title_num(FILE *const f, int *const title_num);

int read_product_line(FILE *const f, s_product *const item);

int get_product_array(FILE *const f, s_product *const products,
int *const products_len);

int print_required(const s_product *const products, const int product_count,
const double entered_price);

#endif // _FUNCS_H_
