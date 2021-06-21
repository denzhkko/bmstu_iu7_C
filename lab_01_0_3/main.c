#include <stdio.h>

#define NORMAL_WEIGHT_INDEX 240.0
#define CM_IN_M 100.0

#define OKAY 0


int main(void)
{
    float h, t, m, nw, im;
    printf("Enter height, chest circumference, mass: ");
    scanf("%f%f%f", &h, &t, &m);

    nw = h * t / NORMAL_WEIGHT_INDEX;
    im = CM_IN_M * CM_IN_M * m / (h * h);

    printf("Normal weight, index of mass: %.5f %.5f\n", nw, im);
    return OKAY;
}
