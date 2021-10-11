#include <stdio.h>

int main(void)
{
    int x[3] = {1, 2, 3};
    printf("%ld\n", sizeof(x)/sizeof(x[0])); // How to print the length of array
    printf("%p\n", x); // Reference of the array 
    printf("%p\n", &x[0]);// Reference of the first element of array x
    return 0;
}