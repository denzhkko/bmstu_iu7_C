#include "../inc/strio.h"

int scanf_size_t(FILE *source, size_t *value)
{
    int c;                                                                

    do
    {
        c = getc(source);                                                                
        LOG_DEBUG("readed $%c$ by code %d", c, c);
    }
    while (EOF != c && (' ' == c || '\n' == c || '\t' == c));

    if ('-' == c)                                                               
    {                                                                           
        LOG_ERROR("%s", "<< Minus scanned");                               
        ungetc(c, source);

        return SCANF_SIZE_T_FAILED;                                              
    }                                                                           
    else if (EOF == c)                                                          
    {                                                                           
        LOG_ERROR("%s", "<< EOF");                                       

        return SCANF_SIZE_T_EOF;                                                      
    }                                                                           

    ungetc(c, source);

    if (1 != fscanf(source, "%zu", value))
    {
        LOG_ERROR("%s", "UNABLE_TO_SCAN_NUM");

        return SCANF_SIZE_T_FAILED;
    }

    LOG_INFO("<< value = %zu", *value);
    return SCANF_SIZE_T_SUCCESS;
}
