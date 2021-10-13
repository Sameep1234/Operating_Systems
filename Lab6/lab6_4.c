#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double compute(int num, double (*func)(double))
{
    double sum = 0.0;
    for (int i = 0; i < num; i++)
    {
        sum += func(i);
    }
    return sum;
}

double ourFunction(double num)
{
    return num / 2.5;
}

void main(void)
{
    printf("%lf\n", compute(100, sin));
    printf("%lf\n", compute(100, cos));
    printf("%lf\n", compute(100, ourFunction));
}