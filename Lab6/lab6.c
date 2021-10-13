#include<stdio.h>
#include<stdlib.h>

int * foo()
{
    int *p = calloc(p, sizeof(int));
    return p;
}

int main()
{
    int *p = foo();
    printf("%d\n", p);
    free(p);
    return 0;
}

/* 
    1. Pointers (Explanation and why is it necessary)
    2. Returning and passing pointers
    3. Difference between C and python (depth view)
    4. Malloc and Calloc in C
    5. Passing arrays
    6. Garbage collection in C (manual)
    7. Length of arrays 
    8. const and others difference in C, python and javascript
    9. Reference count memory management in python
    10. Grammer of a function (check using man command)
    11. Lexicon and parser in C
    12. Memory mapping in C and python (dis module)
    13. C code python open source code github repo (cpython)
    14. Biggest array (lets say 5000 lines (ref: lab6_2.c, localFile))
    15. void pointer
    16. Functions in c and python difference 
    17. Passing functions in c (function pointers (ref: lab6_4.c, localFile))
    18. Runtime dispatch of functions in c
*/