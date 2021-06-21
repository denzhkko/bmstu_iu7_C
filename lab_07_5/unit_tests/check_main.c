#include <check.h>

#include "check_array_io.h"
#include "check_lab_07_array.h"

#define SUITE_FUNC_COUNT 5

typedef Suite *(*suite_func_t)(void);

int main(void)
{
    int num_failed = 0;
    Suite *s;
    SRunner *runner;

    suite_func_t suite_create_arr[SUITE_FUNC_COUNT] = {
        suite_create_count_integers_in_file,
        suite_create_file_to_array,
        suite_create_compare_int,
        suite_create_key,
        suite_create_mysort
    };

    for (int i = 0; i < SUITE_FUNC_COUNT; ++i)
    {
        s = suite_create_arr[i]();

        runner = srunner_create(s);
        srunner_run_all(runner, CK_VERBOSE);
        num_failed += srunner_ntests_failed(runner);
        srunner_free(runner);
        printf("\n");
    }

    printf("Num failed == %d\n", num_failed);
    return (0 == num_failed) ? 0 : -1;
}
