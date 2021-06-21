#include <stdio.h>
#include <string.h>

#include "my_string.h"

int my_str_split(const char *const str,
const char *const sep,
char words[][MAX_WORD_LEN + 1],
int *words_count)
{
    *words_count = 0;

    char *p;
    int word_len;
    
    p = (char *) str;
    while (*p != '\0')
    {
        for (; '\0' != *p && NULL != strchr(sep, *p); ++p);
        char *p_word_start = p;
        
        if ('\0' == *p_word_start)
            break;

        for (; '\0' != *p && NULL == strchr(sep, *p); ++p);
        char *p_word_end = p - 1;
        
        word_len = p_word_end - p_word_start + 1;

        if (word_len > MAX_WORD_LEN)
            return INCORRECT_WORD_LEN;
        
        strncpy(words[*words_count], p_word_start, word_len);
        
        words[*words_count][word_len] = '\0';
        ++(*words_count);
    }
    return OKAY;
}

int count_word_entries(const char *const word,
char words[][MAX_WORD_LEN + 1], const int words_count)
{
    if (words_count < 0)
        return INCORRECT_WORDS_COUNT;

    int count = 0;
    for (int i = 0; i < words_count; ++i)
        if (strcmp(word, words[i]) == 0)
            ++count;

    return count;
}

int my_get_uniq_words(char words_1[][MAX_WORD_LEN + 1],
char words_2[][MAX_WORD_LEN + 1],
int *words_1_count,
int *words_2_count, 
char uniq_words[][MAX_WORD_LEN + 1],
int *uniq_words_count)
{
    if (*words_1_count < 0 || *words_2_count < 0)
        return INCORRECT_MATRIX_SIZE;

    *uniq_words_count = 0;
    for (int i = 0; i < *words_1_count; ++i)
    {
        int count_1 = count_word_entries(words_1[i], words_1, *words_1_count);
        int count_2 = count_word_entries(words_1[i], words_2, *words_2_count);
        
        if (count_1 == INCORRECT_WORDS_COUNT || count_2 == INCORRECT_WORDS_COUNT)
            return INCORRECT_WORDS_COUNT;
        
        if (count_1 + count_2 == 1)
        {
            strcpy(uniq_words[*uniq_words_count], words_1[i]);
            ++*uniq_words_count;
        }
    }

    for (int i = 0; i < *words_2_count; ++i)
    {
        int count_1 = count_word_entries(words_2[i], words_1, *words_1_count);
        int count_2 = count_word_entries(words_2[i], words_2, *words_2_count);

        if (count_1 + count_2 == 1)
        {
            strcpy(uniq_words[*uniq_words_count], words_2[i]);
            ++*uniq_words_count;
        }
    }

    return OKAY;
}

int my_print_answer(char words[][MAX_WORD_LEN + 1],
const int words_count)
{
    if (words_count <= 0)
        return INCORRECT_WORDS_COUNT;

    printf("Result: ");
    for (int i = 0; i < words_count; ++i)
        printf("%s ", words[i]);
    printf("\n");

    return OKAY;
}

int error_processing(const int exit_code)
{
    switch (exit_code)
    {
        case OKAY:
            return OKAY;
        case INCORRECT_INPUT:
            return INCORRECT_INPUT_ERROR;
        case INCORRECT_MATRIX_SIZE:
            return INCORRECT_MATRIX_SIZE_ERROR;
        case INCORRECT_WORDS_COUNT:
            return INCORRECT_WORDS_COUNT_ERROR;
        case INCORRECT_WORD_LEN:
            return INCORRECT_WORD_LEN_ERROR;
        default:
            fprintf(stderr, UNKNOWN_ERROR_MESS);
            return UNKNOWN_ERROR_ERROR;
    }
}
