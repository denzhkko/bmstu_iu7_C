#include "../inc/mystdio.h"

int my_snprintf_string(char *s, size_t available_len, char *is)
{
    size_t s_i = 0, is_i = 0;

    while ('\0' != is[is_i])
    {
        if (s_i < available_len)
            s[s_i] = is[is_i];

        ++s_i;
        ++is_i;
    }

    return (int) is_i;
}

int my_snprintf_short(char *s, size_t available_len, short num)
{
    LOG_INFO(">> available_len = %zu; c = %d", available_len, num);

    size_t i = 0;

    if (num < 0)
    {
        LOG_DEBUG("Num %hd is negative", num);

        if (i < available_len)
            s[i] = '-';
        ++i;
    }
     
    unsigned num_len = get_num_len(num);
    int first_num;
    int ten_power;

    do
    {
        ten_power = power(10, num_len - 1);
        first_num = abs(num / ten_power);

        LOG_DEBUG("num = %d; first_num = %d; num_len = %u", num, first_num, num_len);

        num  = (short) (num % (short) ten_power);
        --num_len;
        
        if (i < available_len)
            s[i] = (char) ('0' + first_num);

        ++i;
    }
    while (ten_power != 1);

    LOG_DEBUG("<< i = %zu", i);
    return (int) i;
}

int my_snprintf_int(char *s, size_t available_len, int num)
{
    LOG_INFO(">> available_len = %zu; c = %d", available_len, num);

    size_t i = 0;

    if (num < 0)
    {
        LOG_DEBUG("Num %d is negative", num);
        if (i < available_len)
            s[i] = '-';
        ++i;
    }
     
    unsigned num_len = get_num_len(num);
    int first_num;
    int ten_power;

    do
    {
        ten_power = power(10, num_len - 1);
        first_num = abs(num / ten_power);

        LOG_DEBUG("num = %d; first_num = %d; num_len = %u; ten_power = %d", num, first_num, num_len, ten_power);

        num %= ten_power;
        --num_len;
        
        if (i < available_len)
            s[i] = (char) ('0' + first_num);

        ++i;
    }
    while (ten_power != 1);

    LOG_DEBUG("<< i = %zu", i);
    return (int) i;
}

int my_snprintf_char(char *s, size_t available_len, char c)
{
    LOG_INFO(">> available_len = %zu; c = %c", available_len, c);

    size_t i = 0;

    while (i < 1)
    {
        if (i < available_len)
            s[i] = c;
        
        ++i;
    }

    LOG_DEBUG("<< i = %zu", i);
    return (int) i;
}

int my_snprintf(char *s, size_t n, const char *format, ...)
{
    int rc;

    va_list vl;
    char va_c;
    int va_int;
    short va_short;
    char *va_string;

    va_start(vl, format);

    size_t src_i = 0, dst_i = 0;

    while ('\0' != format[src_i])
    {
        if ('%' == format[src_i])
        {
            ++src_i;
            switch (format[src_i])
            {
                case 'c':
                    va_c = (char) va_arg(vl, int);
                    rc = my_snprintf_char(s + dst_i, n > dst_i ? n - dst_i - 1 : 0, va_c);
                    dst_i += (unsigned) rc;
                    ++src_i;
                    break;
                case 'd':
                    va_int = va_arg(vl, int);
                    rc = my_snprintf_int(s + dst_i, n > dst_i ? n - dst_i - 1 : 0, va_int);
                    dst_i += (unsigned) rc;
                    ++src_i;
                    break;
                case 'h':
                    ++src_i;
                    switch (format[src_i])
                    {
                        case 'd':
                            va_short = (short) va_arg(vl, int);
                            rc = my_snprintf_short(s + dst_i, n > dst_i ? n - dst_i - 1 : 0, va_short);
                            dst_i += (unsigned) rc;
                            ++src_i;
                            break;
                        default:
                            LOG_ERROR("%s", "Incorrect format");
                            return INCORRECT_FORMAT;
                    }
                    break;
                case 's':
                    va_string = va_arg(vl, char *);
                    rc = my_snprintf_string(s + dst_i, n > dst_i ? n - dst_i - 1 : 0, va_string);
                    dst_i += (unsigned) rc;
                    ++src_i;
                    break;
                case '%':
                    rc = my_snprintf_char(s + dst_i, n > dst_i ? n - dst_i - 1 : 0, '%');
                    dst_i += (unsigned) rc;
                    ++src_i;
                    break;
                default:
                    LOG_ERROR("%s", "Incorrect format");
                    return INCORRECT_FORMAT;
            }
        }
        else
        {
            if (dst_i + 1 < n)
                s[dst_i] = format[src_i];

            ++dst_i;
            ++src_i;
        }
    }

    if (0 != n)
        s[MIN(dst_i, n - 1)] = '\0';

    va_end(vl);

    return (int) dst_i;
}
