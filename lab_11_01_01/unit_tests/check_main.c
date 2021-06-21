#include <stdio.h>
#include <check.h>

#include "check_mystdio.h"

typedef Suite *(*suite_func_t)(void);

int main(void)
{
    int num_failed = 0;
    Suite *s;
    SRunner *runner;

    suite_func_t suite_create_arr[] = {
        suite_my_snprintf,
        suite_my_snprintf_char,
        suite_my_snprintf_int,
        suite_my_snprintf_short,
        suite_my_snprintf_string
    };

    size_t suite_create_arr_len = (sizeof(suite_create_arr) /
    sizeof(suite_create_arr[0]));

    for (size_t i = 0; i < suite_create_arr_len; ++i)
    {
        s = suite_create_arr[i]();

        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);
        num_failed += srunner_ntests_failed(runner);
        srunner_free(runner);
        printf("\n");
    }

    printf("Number failed == %d\n", num_failed);
    return (0 == num_failed) ? 0 : -1;
}
