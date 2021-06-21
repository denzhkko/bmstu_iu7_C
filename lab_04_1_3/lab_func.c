#include <string.h>
#include <stdio.h>

#include "lab_func.h"

int str_split(char *str, char words[][MAX_WORD_LEN + 1], int *words_count)
{
    *words_count = 0;
    char *p;

    p = strtok(str, WORD_SEP);

    while (p)
    {
        if (strlen(p) > MAX_WORD_LEN)
            return INCORRECT_WORD_LEN;

        strcpy(words[*words_count], p);
        p = strtok(NULL, WORD_SEP);
        ++*words_count;
    }

    return OKAY;
}

int form_req_word(char *word, char *req_word)
{
    if (strlen(word) > MAX_WORD_LEN)
        return INCORRECT_WORD_LEN;

    int sym_i = 0;
    for (char *p = word; *p; ++p)
        if (p == strchr(word, *p))
            req_word[sym_i++] = *p;
    req_word[sym_i] = '\0';

    return OKAY;
}

int form_req_str(char words[][MAX_WORD_LEN + 1], const int words_count,
char *req_str)
{
    strcpy(req_str, "");

    if (words_count <= 1)
        return OKAY;

    req_str[0] = '\0';

    char last_word[MAX_WORD_LEN + 1];
    strcpy(last_word, words[words_count - 1]);

    for (int i = words_count - 2; i >= 0; --i)
        if (strcmp(words[i], last_word) != 0)
        {
            char req_word[MAX_WORD_LEN + 1];

            if (INCORRECT_WORD_LEN == form_req_word(words[i], req_word))
                return INCORRECT_WORD_LEN;

            strcat(req_str, req_word);
            strcat(req_str, " ");
        }
    req_str[strlen(req_str) - 1] = '\0';

    return OKAY;
}

int print_res(char *str)
{
    if (strlen(str) == 0)
        return INCORRECT_WORD_LEN;

    printf("Result: %s\n", str);
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
        case INCORRECT_WORD_LEN:
            return INCORRECT_WORD_LEN_ERROR;
        default:
            fprintf(stderr, UNKNOWN_ERROR_MESS);
            return UNKNOWN_ERROR_ERROR;
    }
}
