#include <stdio.h>

#include "my_string.h"

int main(void)
{
    char *sep = " ,;:-.!?\n";
    int exit_code;

    char str1[MAX_STR_LEN + 1], str2[MAX_STR_LEN + 1];
   
    if (NULL == fgets(str1, sizeof(str1), stdin))
        if (OKAY != (exit_code = error_processing(INCORRECT_INPUT)))
            return exit_code;

    if (NULL == fgets(str2, sizeof(str2), stdin))
        if (OKAY != (exit_code = error_processing(INCORRECT_INPUT)))
            return exit_code;

    int words_1_count, words_2_count;

    char words_1[MAX_WORD_COUNT][MAX_WORD_LEN + 1];
    exit_code = my_str_split(str1, sep, words_1, &words_1_count);
    if (OKAY != (exit_code = error_processing(exit_code)))
        return exit_code;

    char words_2[MAX_WORD_COUNT][MAX_WORD_LEN + 1];
    exit_code = my_str_split(str2, sep, words_2, &words_2_count);
    if (OKAY != (exit_code = error_processing(exit_code)))
        return exit_code;

    char uniq_words[2 * MAX_WORD_COUNT][MAX_WORD_LEN + 1];
    int uniq_words_count;

    exit_code = my_get_uniq_words(words_1, words_2, &words_1_count,
    &words_2_count, uniq_words, &uniq_words_count);
    if (OKAY != (exit_code = error_processing(exit_code)))
        return exit_code;

    exit_code = my_print_answer(uniq_words, uniq_words_count);
    if (OKAY != (exit_code = error_processing(exit_code)))
        return exit_code;

    return OKAY;
}
