#include <stdio.h>
#include <math.h>

#define OKAY 0;


int main(void)
{
    float a, b, h, edge, perimeter;
    printf("Enter lengths of bases and height: ");
    scanf("%f%f%f", &a, &b, &h);

    edge = sqrt(h * h + (b - a) * (b - a) / 4.0);
    perimeter = a + b + edge * 2;

    printf("Perimeter: %.5f\n", perimeter);
    return OKAY;
}
