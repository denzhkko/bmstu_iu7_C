#ifndef _MY_STRING_H_
#define _MY_STRING_H_

#define MAX_STR_LEN 256
#define MAX_WORD_LEN 16
#define MAX_WORD_COUNT MAX_STR_LEN / 2

#define INCORRECT_INPUT_ERROR_MESS "Input error\n"
#define INCORRECT_MATRIX_SIZE_MESS "Incorrect matrix size\n"
#define INCORRECT_WORDS_COUNT_MESS "Incorrect words count\n"
#define INCORRECT_WORD_LEN_MESS "Incorrect word len\n"
#define UNKNOWN_ERROR_MESS "Unknow error\n"

#define INCORRECT_INPUT -1
#define INCORRECT_MATRIX_SIZE -2
#define INCORRECT_WORDS_COUNT -3
#define INCORRECT_WORD_LEN -4

#define OKAY 0
#define INCORRECT_INPUT_ERROR 1
#define INCORRECT_MATRIX_SIZE_ERROR 2
#define INCORRECT_WORDS_COUNT_ERROR 3
#define INCORRECT_WORD_LEN_ERROR 4
#define UNKNOWN_ERROR_ERROR 127

int my_str_split(const char *const str,
const char *const sep,
char words[][MAX_WORD_LEN + 1],
int *words_count);

int my_get_uniq_words(char words_1[][MAX_WORD_LEN + 1],
char words_2[][MAX_WORD_LEN + 1],
int *words_1_count,
int *words_2_count, 
char uniq_words[][MAX_WORD_LEN + 1],
int *uniq_words_count);

int my_print_answer(char words[][MAX_WORD_LEN + 1],
const int words_count);

int error_processing(const int exit_code);
#endif
