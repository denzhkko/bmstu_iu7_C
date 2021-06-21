#include <stdio.h>
#include <check.h>

#include "check_listmath.h"

typedef Suite *(*suite_func_t)(void);

int main(void)
{
    int num_failed = 0;
    Suite *s;
    SRunner *runner;

    suite_func_t suite_create_arr[] = {
        suite_num_to_listnum,
        suite_listnum_to_num,
        suite_listnum_copy,
        suite_listnum_mul,
        suite_listnum_sqr,
        suite_listnum_div
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
