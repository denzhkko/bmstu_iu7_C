#include <stdio.h>
#include <check.h>

#include "check_linked_list.h"

typedef Suite *(*suite_func_t)(void);

int main(void)
{
    int num_failed = 0;
    Suite *s;
    SRunner *runner;

    suite_func_t suite_create_arr[] = {
        suite_create_node_create,
        suite_create_list_append,
        suite_create_list_len,
        suite_create_copy,
        suite_create_insert,
        suite_create_sorted_insert,
        suite_create_sort,
        suite_create_pop_front,
        suite_create_remove_duplicates
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

    printf("Num failed == %d\n", num_failed);
    return (0 == num_failed) ? 0 : -1;
}
