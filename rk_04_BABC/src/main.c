#include "../inc/list_methods.h"
#include "../inc/filenames.h"
#include "../inc/rc.h"

int main(void)
{
    int rc;

    char_list_t *head = char_list_read(FILENAME_IN);

    if (NULL == head)
        return READ_FAILED;

    // reverse(head);

    rc = char_list_print(FILENAME_OUT, head);

    if (OKAY != rc)
        return rc;

    return 0;
}
