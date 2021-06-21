#include <check.h>

#include "check_matrix_methods.h"
#include "check_strio.h"

#define SUITE_FUNC_COUNT                6

typedef Suite *(*suite_func)(void);

int main(void)
{
    int num_failed = 0;
    Suite *suite;
    SRunner *runner;

    suite_func suite_funcs[SUITE_FUNC_COUNT] = {
    suite_file_to_double_matrix,
    suite_get_invert_double_matrix,
    suite_get_double_matrix_sum,
    suite_get_double_matrix_product,
    suite_is_file_double_matrix_eq,
    suite_scanf_size_t
    };

    for (int i = 0; i < SUITE_FUNC_COUNT; ++i)
    {
        suite = suite_funcs[i]();

        runner = srunner_create(suite);
        srunner_run_all(runner, CK_VERBOSE);
        num_failed += srunner_ntests_failed(runner);
        srunner_free(runner);
        printf("\n");
    }

    printf("Num failed == %d\n", num_failed);
    return num_failed;
}
