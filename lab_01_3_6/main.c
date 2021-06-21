#include <stdio.h>
#include <math.h>

#define INPUT_VAR_NUM 6
#define REAL_TOL 1e-7

#define BELOW_LINE 2
#define ON_LINE 1
#define OVER_LINE 0
#define LINE_POINTS_COINCIDENCE -2
#define VERTICAL_LINE -3

#define OKAY 0
#define INPUT_ERROR 1
#define LINE_POINTS_COINCIDENCE_ERROR 2
#define VERTICAL_LINE_ERROR 3


int point_pos_determination(float x1, float y1, float x2,
float y2, float x_p, float y_p)
{
    if (fabs(x2 - x1) < REAL_TOL && fabs(y2 - y1) < REAL_TOL)
        return LINE_POINTS_COINCIDENCE;

    if (fabs(x2 - x1) < REAL_TOL && fabs(x2 - x_p) < REAL_TOL)
        return ON_LINE;

    if (fabs(x2 - x1) < REAL_TOL)
        return VERTICAL_LINE;

    float y_p_straight = (x_p - x2) * (y1 - y2) / (x1 - x2) + y2;

    if (fabs(y_p_straight - y_p) < REAL_TOL)
        return ON_LINE;
    else if (y_p > y_p_straight)
        return OVER_LINE;
    else
        return BELOW_LINE;
}


int main(void)
{
    float x1, y1, x2, y2, x_p, y_p;
    int rc;
    int p_pos;

    printf("Enter the coordinates of the points of the line and the plane: ");
    rc = scanf("%f%f%f%f%f%f", &x1, &y1, &x2, &y2, &x_p, &y_p);

    if (INPUT_VAR_NUM == rc)
    {
        p_pos = point_pos_determination(x1, y1, x2, y2, x_p, y_p);

        if (LINE_POINTS_COINCIDENCE == p_pos)
        {
            printf("Coincidence of line points\n");
            return LINE_POINTS_COINCIDENCE_ERROR;
        }

        if (VERTICAL_LINE == p_pos)
        {
            printf("Line is vertical and point is not on it\n");
            return VERTICAL_LINE_ERROR;
        }

        if (OVER_LINE == p_pos)
            printf("OVER_LINE %d\n", p_pos);
        else if (ON_LINE == p_pos)
            printf("ON_LINE %d\n", p_pos);
        else
            printf("BELOW_LINE %d\n", p_pos);
        return OKAY;
    }
    else
    {
        printf("Input error\n");
        return INPUT_ERROR;
    }
}
