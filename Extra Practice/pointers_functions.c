#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <math.h>

#define ll long long int
#define ld long double

/*
    Passing a function pointer as the argument
    Here the specification of the function should be such that it takes in double as parameters
    and returns double as the answer.

    Further, if we want a universal function pointer, we can write void * instead of double that
    accepts any type of argument.
*/
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

void change(int *p) // Declare function parameter as pointer
{
    *p = *p + 10;
}

int *larger (int *x, int *y) // Takes pointer as argument and returns pointer as well
{
    if(*x > *y)
        return(x); // Return the address of a
    else
        return(y); // Reutrn the address of b
}

int main()
{
    /* Function arguments */
    int x = 20;
    change(&x); // Pass argument as address i.e basically pass a pointer
    printf("%d\n", x); // Prints 30

    /* Functions returning pointers */
    int a = 10;
    int b = 20;
    printf("Address before calling: %d\n", &b);
    int *result = larger(&a, &b); // Passing addresses and getting pointer result
    printf("Address after calling: %d\n", result); // This must be equal to &b
    printf("%d\n", *result); // Printing the values pointed by result

    /* Pointers to a function */
    printf("%lf\n", compute(100, sin));
    printf("%lf\n", compute(100, cos));
    printf("%lf\n", compute(100, ourFunction));

    return 0;
}