#include <stdio.h>

#define EMPTY_BOTTLE_COST 20
#define WATER_BOTTLE_COST 45

#define OKAY 0


int main(void)
{
    int s, num_bot = 0;
    printf("Enter the amount of money: ");
    scanf("%d", &s);

    num_bot = (s - EMPTY_BOTTLE_COST) / (WATER_BOTTLE_COST - EMPTY_BOTTLE_COST);

    printf("Max number of bottles: %d\n", num_bot);
    return OKAY;
}
