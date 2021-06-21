#include <stdio.h>

#define INPUT_VAR_NUM 2

#define INCORRECT_DATA -2

#define OKAY 0
#define INPUT_ERROR 1
#define INCORRECT_DATA_ERROR 2


int gcd(int a, int b)
{
    if (a <= 0 || b <= 0)
        return INCORRECT_DATA;

    while (a != 0 && b != 0)
    {
        if (a > b)
            a %= b;
        else
            b %= a;
    }

    return a + b;
}


int main(void)
{
    int a, b, rc;
    int gcd_res;

    printf("Enter two integers: ");
    rc = scanf("%d%d", &a, &b);

    if (INPUT_VAR_NUM == rc)
    {
        gcd_res = gcd(a, b);

        if (INCORRECT_DATA == gcd_res)
        {
            printf("Incorrect data\n");
            return INCORRECT_DATA_ERROR;
        }
        printf("GCD = %d\n", gcd_res);
        return OKAY;
    }
    else
    {
        printf("Input error\n");
        return INPUT_ERROR;
    }
}
