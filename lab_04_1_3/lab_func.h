#ifndef _LAB_04_1_3_FUNC_

#define _LAB_04_1_3_FUNC_

#define MAX_STR_LEN 256
#define MAX_WORD_LEN 16
#define MAX_WORD_COUNT MAX_STR_LEN / 2

#define WORD_SEP " ,;:-.!?\n"

#define OKAY 0

#define INCORRECT_INPUT_MESS "Incorrect input\n"
#define INCORRECT_WORD_LEN_MESS "Incorrect word len\n"
#define UNKNOWN_ERROR_MESS "Unknown error\n"

#define INCORRECT_INPUT -1
#define INCORRECT_WORD_LEN -2
#define UNKNOWN_ERROR -127

#define INCORRECT_INPUT_ERROR 1
#define INCORRECT_WORD_LEN_ERROR 2
#define UNKNOWN_ERROR_ERROR 127

int str_split(char *str, char words[][MAX_WORD_LEN + 1], int *words_count);

int form_req_word(char *word, char *req_word);

int form_req_str(char words[][MAX_WORD_LEN + 1], const int words_count,
char *req_str);

int print_res(char *str);

int error_processing(const int exit_code);
#endif
