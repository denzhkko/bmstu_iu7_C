#include <stdio.h>
#include <math.h>

#define INPUT_VAR_NUM 2
#define REAL_TOL 1e-7

#define X_MAX_VALUE 1.0
#define X_MIN_VALUE -1.0
#define EPS_MAX_VALUE 1.0

#define INCORRECT_X 4.0
#define INCORRECT_EPS 8.0

#define OKAY 0
#define INPUT_ERROR 1
#define INCORRECT_X_ERROR 4
#define INCORRECT_EPS_ERROR 8


double calc_s(double x, double eps)
{
    if (x > X_MAX_VALUE || x < X_MIN_VALUE)
        return INCORRECT_X;

    if (eps >= EPS_MAX_VALUE)
        return INCORRECT_EPS;

    double memb_of_seq = x;
    double s = memb_of_seq;

    for (int i = 2; fabs(memb_of_seq) > eps; ++i)
    {
        memb_of_seq = x * x * (2 * (i - 1) - 1) * (-memb_of_seq) / (2 * i - 1);
        s += memb_of_seq;
    }

    return s;
}


int main(void)
{
    double x, eps, s, f, abs_error, rel_error;
    int rc;

    printf("Enter value x, eps: ");
    rc = scanf("%lf%lf", &x, &eps);

    if (INPUT_VAR_NUM == rc)
    {
        s = calc_s(x, eps);

        if (fabs(s - INCORRECT_X) < REAL_TOL)
        {
            printf("Absolute value of x should not be more than one\n");
            return INCORRECT_X_ERROR;
        }

        if (fabs(s - INCORRECT_EPS) < REAL_TOL)
        {
            printf("Value of eps should not be equal or more than one\n");
            return INCORRECT_EPS_ERROR;
        }

        f = atan(x);
        abs_error = fabs(f - s);
        rel_error = fabs((f - s) / f);

        printf("s(x) = %.6lf\n", s);
        printf("f(x) = %.6lf\n", f);
        printf("Absolute error = %.6lf\n", abs_error);

        if (fabs(f) < REAL_TOL)
            printf("Unable to cals relative error\n");
        else
            printf("Relative error = %.6lf\n", rel_error);

        return OKAY;
    }
    else
    {
        printf("Input error\n");
        return INPUT_ERROR;
    }
}
