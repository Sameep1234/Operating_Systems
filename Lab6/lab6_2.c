#include<stdio.h>
#include<stdlib.h>

void f(int *arr)
{
    arr[32] = 1;
}

void main(void)
{
    int *arr = calloc(5000, sizeof(int)); // set a pointer to the array of 5000 lines and initilize all values to 0
    // This array is stored on heap and not on stack
    for(int i = 0;i<5000;i++)
    {
        arr[i] = 400 * i;
    }
    printf("Before calling: %d\n", arr[32]);
    f(arr);
    printf("After calling: %d\n", arr[32]);
    free(arr);
}