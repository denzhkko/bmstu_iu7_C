#include "../inc/nonstdio.h"

int skip_sep_symbols(FILE *source)
{
    int count = 0;

    int c;
    while (EOF != (c = fgetc(source)) && (' ' == c || '\n' == c))
        ++count;

    if (EOF != c)
        ungetc(c, source);

    return count;
}

bool next_char_minus(FILE *const f)
{
    int c = getc(f);
    bool res = false;

    if (EOF == c)
    {
        LOG_ERROR("%s", "<< Empty line");
        return false;
    }
    else if ('-' == c)
    {
        LOG_ERROR("%s", "<< Negative title num");
        res = true;
    }
    ungetc(c, f);

    LOG_INFO("<< %s", res ? "true" : "false");
    return res;
}

int read_unsigned(FILE *const f, unsigned *const num)
{
    assert(NULL != f);

    unsigned temp_num;

    skip_sep_symbols(f);

    if (next_char_minus(f))
        return ERR_NEGATIVE_NUM;

    if (1 != fscanf(f, "%u", &temp_num))
    {
        LOG_ERROR("%s", "Num getting failed");
        return ERR_INCORRECT_INPUT;
    }

    *num = temp_num;

    LOG_INFO("<< Number == %u", *num);
    return OKAY;
}
