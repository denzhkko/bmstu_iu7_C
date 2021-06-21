#include <stdio.h>
#include <string.h>

#include "my_string.h"

#define TRUE 1
#define FALSE 0

void print_cmp_res(const char *dt_str, const char *dt_keys,
const int test_number, int *is_all_res_same)
{
    char *str_res = strpbrk(dt_str, dt_keys);
    if (str_res)
        printf("%s\n", str_res);
    else
        printf("NULL\n");

    char *my_res = my_strpbrk(dt_str, dt_keys);
    if (my_res)
        printf("%s\n", my_res);
    else
        printf("NULL\n");

    if (str_res == my_res)
        printf("%d test: success\n\n", test_number);
    else
    {
        *is_all_res_same = FALSE;
        printf("%d test: error\n\n", test_number);
    }
}


int main(void)
{
    int is_all_res_same = TRUE;

    // 1 key test
    char *dt_1_str = "Hello world";
    char *dt_1_keys = "e";
    print_cmp_res(dt_1_str, dt_1_keys, 1, &is_all_res_same);

    // 2 keys test
    char *dt_2_str = "Hello world";
    char *dt_2_keys = "oe";
    print_cmp_res(dt_2_str, dt_2_keys, 2, &is_all_res_same);

    // unused keys test
    char *dt_3_str = "Hello world";
    char *dt_3_keys = "123";
    print_cmp_res(dt_3_str, dt_3_keys, 3, &is_all_res_same);

    // not keys test
    char *dt_4_str = "Hello world";
    char *dt_4_keys = "";
    print_cmp_res(dt_4_str, dt_4_keys, 4, &is_all_res_same);

    if (is_all_res_same)
    {
        printf("\nAll test passed successfully\n");
        return 0;
    }

    printf("\nSome differences in tests\n");
    return 1;
}
