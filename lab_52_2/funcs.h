#ifndef _FUNCS_H_
#define _FUNCS_H_

#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#define MAX_NAME_LEN 30
#define MAX_PRODUCER_LEN 15
#define MAX_NUM_LEN 10

#define TRUE 1
#define FALSE 0

#define FILE_CANNOT_BE_OPENED -1
#define FSEEK_FAILED -2
#define FTELL_FAILED -3
#define EMPTY_FILE -4
#define INCORRECT_FILE_SIZE -5
#define FCLOSE_FAILED -6
#define INCORRECT_SUBSTR_LEN -7
#define NO_MATCHING_ITEMS -8
#define INCORRECT_PRODUCT_FIELD -9
#define FILE_ISNOT_SORTED -10
#define INCORRECT_PARAMETERS -53
#define UNKNOWN_EXIT_CODE -127

#define FSEEK_FAILED_MESS "fseek failed\n"
#define FTELL_FAILED_MESS "ftell failed\n"
#define EMPTY_FILE_MESS "Empty file\n"
#define INCORRECT_FILE_SIZE_MESS "Incorrect file size\n"
#define INCORRECT_SUBSTR_LEN_MESS "Incorrect substring length\n"
#define NO_MATCHING_ITEMS_MESS "No matching items\n"
#define INCORRECT_PRODUCT_FIELD_MESS "Incorrect input field\n"
#define FILE_ISNOT_SORTED_MESS "File is not sorted\n"
#define INCORRECT_PARAMETERS_MESS "Enter: ./main.exe <command> <files>\n" \
"Available commands:\n" \
"sb - sort by price, quantity    : ./main.exe sb file_in file_out\n" \
"fb - find by substr at name end : ./main.exe fb file_in substr\n" \
"ab - append item to sorted file : ./main.exe ab file_in_out\n"
#define UNKNOWN_EXIT_CODE_MESS "Unknown error\n" 

#define OKAY 0
#define FILE_CANNOT_BE_OPENED_ERROR 1
#define FSEEK_FAILED_ERROR 2
#define FTELL_FAILED_ERROR 3
#define EMPTY_FILE_ERROR 4
#define INCORRECT_FILE_SIZE_ERROR 5
#define FCLOSE_FAILED_ERROR 6
#define INCORRECT_SUBSTR_LEN_ERROR 7
#define NO_MATCHING_ITEMS_ERROR 8
#define INCORRECT_PRODUCT_FIELD_ERROR 9
#define FILE_ISNOT_SORTED_ERROR 10
#define INCORRECT_PARAMETERS_ERROR 53
#define UNKNOWN_EXIT_CODE_ERROR 127

struct product
{
    char name[MAX_NAME_LEN + 1];
    char producer[MAX_PRODUCER_LEN + 1];
    uint32_t price;
    uint32_t quantity;
};

int get_file_size(FILE *f, size_t *const size);

int sort_file(FILE *f_in, FILE *f_out);

int find_items(FILE *f, char *substr);

int append_to_sorted_file(FILE *f);

int process_exit_code(const int exit_code);

#endif /* _FUNCS_H_ */
