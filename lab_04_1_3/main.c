#include <stdio.h>

#include "lab_func.h"

#define INCORRECT_INPUT_ERROR 1
#define INCORRECT_WORD_LEN_ERROR 2

int main(void)
{
    int exit_code;

    char str[MAX_STR_LEN + 1];

    if (NULL == fgets(str, sizeof(str), stdin))
        if (OKAY != (exit_code = error_processing(INCORRECT_INPUT_ERROR)))
            return exit_code; 

    int words_count;
    char words[MAX_WORD_COUNT][MAX_WORD_LEN + 1];

    exit_code = str_split(str, words, &words_count);
    if (OKAY != (exit_code = error_processing(exit_code)))
        return exit_code;

    char req_str[MAX_STR_LEN];
    exit_code = form_req_str(words, words_count, req_str);
    if (OKAY != (exit_code = error_processing(exit_code)))
        return exit_code;


    exit_code = print_res(req_str);
    if (OKAY != (exit_code = error_processing(exit_code)))
        return exit_code;


    return OKAY;
}
