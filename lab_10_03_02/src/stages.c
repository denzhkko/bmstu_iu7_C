#include "../inc/stages.h"

int stage_input(struct args *args)
{
    int rc, rc_num_1, rc_num_2;

    char keyword[KEYWORD_STR_LEN + 1];
    
    if (1 != (rc = scanf("%3s", keyword)))
    {
        LOG_ERROR("Key word not read; rc = %d", rc);
        return ERR_INCORRECT_INPUT;
    }

    struct args tmp_args;

    if (!strcmp(keyword, STR_OUT))
    {
        LOG_TRACE("%s", "out");
        tmp_args.selected_case = CASE_OUT;
        tmp_args.num_2 = 0;

        rc_num_1 = read_unsigned(stdin, &tmp_args.num_1);

        if (OKAY != rc_num_1)
        {
            LOG_ERROR("Number for output not read; rc = %d", rc);
            return rc_num_1;
        }

        if (0 == tmp_args.num_1)
        {
            LOG_ERROR("%s", "Zero entered");
            return ERR_INCORRECT_INPUT;
        }
    }
    else if (!strcmp(keyword, STR_MUL))
    {
        LOG_TRACE("%s", "mul");
        tmp_args.selected_case = CASE_MUL;

        rc_num_1 = read_unsigned(stdin, &tmp_args.num_1);
        rc_num_2 = read_unsigned(stdin, &tmp_args.num_2);

        if (OKAY != rc_num_1 || OKAY != rc_num_2)
        {
            LOG_ERROR("Number for mul not read; rc_num_1 = %d; rc_num_2 = %d ",
            rc_num_1, rc_num_2);

            return OKAY != rc_num_1 ? rc_num_1 : rc_num_2;
        }

        if (0 == tmp_args.num_1 || 0 == tmp_args.num_2)
        {
            LOG_ERROR("%s", "Zero entered");
            return ERR_INCORRECT_INPUT;
        }
    }
    else if (!strcmp(keyword, STR_SQR))
    {
        LOG_TRACE("%s", "sqr");
        tmp_args.selected_case = CASE_SQR;
        tmp_args.num_2 = 0;

        rc_num_1 = read_unsigned(stdin, &tmp_args.num_1);

        if (OKAY != rc_num_1)
        {
            LOG_ERROR("Number for square not read; rc = %d", rc);
            return rc_num_1;
        }

        if (0 == tmp_args.num_1)
        {
            LOG_ERROR("%s", "Zero entered");
            return ERR_INCORRECT_INPUT;
        }
    }
    else if (!strcmp(keyword, STR_DIV))
    {
        LOG_TRACE("%s", "div");
        tmp_args.selected_case = CASE_DIV;

        rc_num_1 = read_unsigned(stdin, &tmp_args.num_1);
        rc_num_2 = read_unsigned(stdin, &tmp_args.num_2);

        if (OKAY != rc_num_1 || OKAY != rc_num_2)
        {
            LOG_ERROR("Number for div not read; rc_num_1 = %d; rc_num_2 = %d ",
            rc_num_1, rc_num_2);

            return OKAY != rc_num_1 ? rc_num_1 : rc_num_2;
        }

        if (0 == tmp_args.num_1 || 0 == tmp_args.num_2)
        {
            LOG_ERROR("%s", "Zero entered");
            return ERR_INCORRECT_INPUT;
        }
    }
    else
    {
        tmp_args.selected_case = CASE_UNKNOWN;
        LOG_ERROR("Unknown keyword: %s", keyword);
        return ERR_UNKNOWN_KEYWORD;
    }

    *args = tmp_args;

    LOG_INFO("<< num_1 = %u; num_2 = %u; selected_case = %u",
    args->num_1, args->num_2, args->selected_case);
    return OKAY;
}

int run_stages()
{
    int rc, grc = OKAY;
    struct args args;

    rc = stage_input(&args);

    if (OKAY != rc)
        return rc;

    struct num_node *listnum_1 = NULL, *listnum_2 = NULL;

    switch (args.selected_case)
    {
        case CASE_OUT:
            listnum_1 = num_to_listnum(args.num_1);
            if (NULL != listnum_1)
            {
                listnum_print(stdout, listnum_1);
            }
            listnum_free(listnum_1);
            break;
        case CASE_MUL:
            listnum_1 = num_to_listnum(args.num_1);
            listnum_2 = num_to_listnum(args.num_2);
            if (NULL != listnum_1 && NULL  != listnum_2)
            {
                struct num_node *comp = listnum_mul(listnum_1, listnum_2);
                if (NULL != comp)
                {
                    listnum_print(stdout, comp);

                    listnum_free(comp);
                }
                else
                {
                    LOG_ERROR("%s", "Allocation for comp failed");
                    return ERR_ALLOCATION_FAILED;
                }
            }
            listnum_free(listnum_2);
            listnum_free(listnum_1);
            break;
        case CASE_SQR:
            listnum_1 = num_to_listnum(args.num_1);
            if (NULL != listnum_1)
            {
                struct num_node *sqr = listnum_sqr(listnum_1);
                if (NULL != sqr)
                {
                    listnum_print(stdout, sqr);

                    listnum_free(sqr);
                }
                else
                {
                    LOG_ERROR("%s", "Allocation for comp failed");
                    return ERR_ALLOCATION_FAILED;
                }
            }
            listnum_free(listnum_1);
            break;
        case CASE_DIV:
            listnum_1 = num_to_listnum(args.num_1);
            listnum_2 = num_to_listnum(args.num_2);
            if (NULL != listnum_1 && NULL  != listnum_2)
            {
                struct num_node *div;
                rc = listnum_div(listnum_1, listnum_2, &div);
                if (OKAY == rc)
                {
                    listnum_print(stdout, div);
                    listnum_free(div);
                }
                else if (ERR_ZERO_GOT == rc)
                {
                    LOG_ERROR("%s", "Zero got");
                    grc = rc;
                }
                else
                {
                    LOG_ERROR("%s", "div failed");
                    grc = rc;
                }
            }
            listnum_free(listnum_2);
            listnum_free(listnum_1);
            break;
        default:
            LOG_ERROR("%s", "Unknown case");
            return ERR_UNKNOWN;
    }

    return grc;
}
