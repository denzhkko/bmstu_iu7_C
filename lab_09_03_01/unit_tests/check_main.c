#include <stdio.h>
#include <check.h>

#include "check_lab_io.h"
#include "check_product.h"

typedef Suite *(*suite_func_t)(void);

#define SUITE_FUNC_COUNT                3

int main(void)
{
    int num_failed = 0;
    Suite *s;
    SRunner *runner;

    suite_func_t suite_create_arr[SUITE_FUNC_COUNT] = {
        suite_create_vector_append_product,
        suite_create_get_title_num,
        suite_create_read_product_line
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
