#include "check_matrix_methods.h"

#define DIR "unit_tests/files/matrix_methods/"
#define RES_FILE_START "res_"

bool is_matrix_eq(matrix_t *dmatrix, double *smatrix, size_t n, size_t m)
{
    LOG_INFO(">> n = %zu; m = %zu", n, m);
    size_t dmatrix_row = matrix_get_row_count(dmatrix);
    size_t dmatrix_col = matrix_get_column_count(dmatrix);

    if (n != dmatrix_row)
    {
        LOG_INFO("Row count is not equal: %zu vs %zu", n, dmatrix_row);
        return false;
    }

    if (m != dmatrix_col)
    {
        LOG_INFO("Col count is not equal: %zu vs %zu", m, dmatrix_col);
        return false;
    }

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            double smatrix_value = *(smatrix + i * m + j);
            double dmatrix_value = matrix_get_double_at(dmatrix, i, j);

            LOG_DEBUG("d[%zu][%zu] = %lf; s[%zu][%zu] = %lf",
            i, j, dmatrix_value, i, j, smatrix_value);

            if (fabs(dmatrix_value - smatrix_value) >= DOUBLE_TOL)
                return false;
        }
    }

    return true;
}

START_TEST(ftdm_neg)
{
    matrix_t *dmatrix = file_to_double_matrix(DIR "ftdm_neg_incorrect.txt");
    ck_assert_ptr_eq(NULL, dmatrix);
}

#define N 2
#define M 3
START_TEST(ftdm_pos)
{
    char *FILENAME = DIR "ftdm_pos.txt";

    double smatrix[N][M] = {{1.5, 2.4, 1.3}, {-1.7, 0.1, 1.3}};

    matrix_t *dmatrix = file_to_double_matrix(FILENAME);
    ck_assert_ptr_ne(NULL, dmatrix);

    bool res = is_matrix_eq(dmatrix, (double *) smatrix, N, M);
    ck_assert_int_eq(true, res);
    matrix_free(dmatrix);
}
#undef N
#undef M

Suite *suite_file_to_double_matrix(void)
{
    Suite *suite;

    TCase *tcase_neg;
    TCase *tcase_pos;

    suite = suite_create("file_to_double_matrix");

    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_neg, ftdm_neg);

    suite_add_tcase(suite, tcase_neg);

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_neg, ftdm_pos);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

#define FILENAME_IN "gidm_pos_f.txt"
#define FILENAME_OUT "gidm_pos_out.txt"
START_TEST(gidm_pos)
{
    int rc;

    matrix_t *matrix = file_to_double_matrix(DIR FILENAME_IN);
    ck_assert_ptr_ne(NULL, matrix);

    rc = invert_double_matrix(&matrix);
    ck_assert_int_eq(OKAY, rc);

    double_matrix_to_file(matrix, DIR RES_FILE_START FILENAME_OUT);

    matrix_free(matrix);

    rc = is_file_double_matrix_eq(DIR FILENAME_OUT,
    DIR RES_FILE_START FILENAME_OUT);
    ck_assert_int_eq(FILE_EQUAL, rc);
}
#undef FILENAME_IN
#undef FILENAME_OUT

Suite *suite_get_invert_double_matrix(void)
{
    Suite *suite;

    TCase *tcase_pos;

    suite = suite_create("get_invert_double_matrix");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, gidm_pos);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

#define FILENAME_F "gdms_pos_f.txt"
#define FILENAME_S "gdms_pos_s.txt"
#define FILENAME_SUM "gdms_pos_out.txt"
START_TEST(gdsm_pos)
{
    int rc;

    matrix_t *matrix_f = file_to_double_matrix(DIR FILENAME_F);
    ck_assert_ptr_ne(NULL, matrix_f);

    matrix_t *matrix_s = file_to_double_matrix(DIR FILENAME_S);
    ck_assert_ptr_ne(NULL, matrix_s);

    matrix_t *matrix_sum = get_double_matrix_sum(matrix_f, matrix_s);
    ck_assert_ptr_ne(NULL, matrix_sum);

    double_matrix_to_file(matrix_sum, DIR RES_FILE_START FILENAME_SUM);

    matrix_free(matrix_f);
    matrix_free(matrix_s);
    matrix_free(matrix_sum);

    rc = is_file_double_matrix_eq(DIR FILENAME_SUM,
    DIR RES_FILE_START FILENAME_SUM);
    ck_assert_int_eq(FILE_EQUAL, rc);
}
#undef FILENAME_SUM
#undef FILENAME_S
#undef FILENAME_F

Suite *suite_get_double_matrix_sum(void)
{
    Suite *suite;

    TCase *tcase_pos;

    suite = suite_create("get_double_matrix_sum");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, gdsm_pos);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}

#define FILENAME_F "gdmp_pos_f.txt"
#define FILENAME_S "gdmp_pos_s.txt"
#define FILENAME_PRODUCT "gdmp_pos_out.txt"
START_TEST(gdmp_pos)
{
    int rc;

    matrix_t *matrix_f = file_to_double_matrix(DIR FILENAME_F);
    ck_assert_ptr_ne(NULL, matrix_f);

    matrix_t *matrix_s = file_to_double_matrix(DIR FILENAME_S);
    ck_assert_ptr_ne(NULL, matrix_s);

    matrix_t *matrix_product = get_double_matrix_product(matrix_f, matrix_s);
    ck_assert_ptr_ne(NULL, matrix_product);

    double_matrix_to_file(matrix_product, DIR RES_FILE_START FILENAME_PRODUCT);

    matrix_free(matrix_f);
    matrix_free(matrix_s);
    matrix_free(matrix_product);

    rc = is_file_double_matrix_eq(DIR FILENAME_PRODUCT,
    DIR RES_FILE_START FILENAME_PRODUCT);
    ck_assert_int_eq(FILE_EQUAL, rc);
}
#undef FILENAME_S
#undef FILENAME_F

Suite *suite_get_double_matrix_product(void)
{
    Suite *suite;

    TCase *tcase_pos;

    suite = suite_create("get_double_matrix_product");

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, gdmp_pos);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}
#define NEGPOS_IFDME(F_FILENAME, S_FILENAME, RC) \
int rc = is_file_double_matrix_eq(F_FILENAME, S_FILENAME); \
ck_assert_int_eq(RC, rc);

START_TEST(ifdme_neg_incorrect_size)
{
    NEGPOS_IFDME(DIR "ifdme_neg_incorrect_size_f.txt",
    DIR "ifdme_neg_incorrect_size_s.txt", INCORRECT_FILE);
}
END_TEST

START_TEST(ifdme_neg_incorrect_elems)
{
    NEGPOS_IFDME(DIR "ifdme_neg_incorrect_elems_f.txt",
    DIR "ifdme_neg_incorrect_elems_s.txt", INCORRECT_FILE);
}
END_TEST

START_TEST(ifdme_neg_cannot_open_file)
{
    NEGPOS_IFDME(DIR "ifdme_neg_incorrect_elems_f.txt",
    DIR "ifdme_neg_unexist.txt", FILE_CANNOT_BE_OPENED);
}
END_TEST

START_TEST(ifdme_pos_eq)
{
    NEGPOS_IFDME(DIR "ifdme_pos_equal_f.txt",
    DIR "ifdme_pos_equal_s.txt", FILE_EQUAL);
}
END_TEST

START_TEST(ifdme_pos_not_eq)
{
    NEGPOS_IFDME(DIR "ifdme_pos_not_equal_f.txt",
    DIR "ifdme_pos_not_equal_s.txt", FILE_NOT_EQUAL);
}
END_TEST

Suite *suite_is_file_double_matrix_eq(void)
{
    Suite *suite;

    TCase *tcase_neg;
    TCase *tcase_pos;

    suite = suite_create("file_to_double_matrix");

    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_neg, ifdme_neg_incorrect_size);
    tcase_add_test(tcase_neg, ifdme_neg_incorrect_elems);
    tcase_add_test(tcase_neg, ifdme_neg_cannot_open_file);

    suite_add_tcase(suite, tcase_neg);

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, ifdme_pos_eq);
    tcase_add_test(tcase_pos, ifdme_pos_not_eq);

    suite_add_tcase(suite, tcase_pos);

    return suite;
}
