#include "../inc/stages.h"

#define FCLOSE(F, FILENAME, GRC)    \
if (EOF == fclose(F))   \
{   \
    LOG_ERROR("flose for %s failed", FILENAME); \
    grc = UNABLE_TO_CLOSE_FILE; \
}

int run_stages(args_t *args)
{
    int rc;
    node_t *head = NULL, *head_uniq = NULL;

    if (OKAY != (rc = stage_input(args->filename_in, &head)))
    {
        LOG_ERROR("Stage input failed with rc = %d", rc);
        list_free(&head);
        return rc;
    }

    if (NULL == head)
    {
        list_free(&head_uniq);
        number_list_free(&head);
        return EMPTY_FILE;
    }

    if (OKAY != (rc = stage_process(&head, &head_uniq)))
    {
        LOG_ERROR("Stage process failed with rc = %d", rc);
        list_free(&head_uniq);
        number_list_free(&head);
        return rc;
    }

    if (OKAY != (rc =
    stage_output(head, head_uniq, args->filename_out_f, args->filename_out_s)))
    {
        LOG_ERROR("Stage output failed with rc = %d", rc);
        list_free(&head_uniq);
        number_list_free(&head);
        return rc;
    }

    list_free(&head_uniq);
    number_list_free(&head);

    return OKAY;
}

int stage_input(char *filename, node_t **head)
{
    LOG_TRACE(">> filename = %s", filename);

    int grc;
    *head = NULL;

    grc = file_to_list_by_filename(filename, head);

    LOG_TRACE("<< grc = %d", grc);
    return grc;
}

int stage_process(node_t **head, node_t **head_uniq)
{
    LOG_TRACE("%s", ">> Called");

    int rc;

    *head = sort(*head, *number_comparator);
    rc = copy(*head, head_uniq);

    if (OKAY != rc)
    {
        LOG_ERROR("%s", "Copy failed");
        return ALLOCATION_FAILED;
    }

    remove_duplicates(head_uniq, *number_comparator);

    LOG_TRACE("%s", "<< default return OKAY");
    return OKAY;
}

int stage_output_fopen(char *filename, char *filename_uniq,
FILE **f, FILE **f_uniq)
{
    LOG_TRACE("%s", ">> Called");

    int grc = OKAY;
    *f = fopen(filename, "w");

    if (NULL == *f)
    {
        LOG_ERROR("%s: %s", filename, strerror(errno));
        return UNABLE_TO_OPEN_FILE;
    }

    *f_uniq = fopen(filename_uniq, "w");

    if (NULL == *f_uniq)
    {
        LOG_ERROR("%s: %s", filename_uniq, strerror(errno));
        grc = UNABLE_TO_OPEN_FILE;
        FCLOSE(*f, filename, grc)
        return grc;
    }

    LOG_TRACE("%s", "<< default return OKAY");
    return OKAY;
}

int stage_output(node_t *head, node_t *head_uniq,
char *filename, char *filename_uniq)
{
    LOG_TRACE("%s", ">> Called");
    int rc, grc = OKAY;

    FILE *f, *f_uniq;

    if (OKAY != (rc = stage_output_fopen(filename, filename_uniq, &f, &f_uniq)))
    {
        LOG_ERROR("%s", "fopen failed");
        return rc;
    }

    list_to_source_by_fptr(head, f);
    list_to_source_by_fptr(head_uniq, f_uniq);

    FCLOSE(f, filename, grc);
    FCLOSE(f_uniq, filename_uniq, grc);

    LOG_TRACE("%s", "<< default return OKAY");
    return grc;
}

#undef FCLOSE
