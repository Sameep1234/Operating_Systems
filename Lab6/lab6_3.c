#include<stdio.h>
#include<stdlib.h>

void main(void)
{
    int x = 1;
    void *p = &x;
    float y = 2.56;
    p = &y;
    // This is valid. Explanation done later
}