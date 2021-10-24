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

#define ll long long int
#define ld long double

int main()
{
    int quantity = 180;
    printf("%d %u\n", quantity, &quantity); // Accessing the address of quanity ('&' sign is used to access address)

    int *p = &quantity; // Always store the address into an integer pointer
    int y = *p; // Accessing quantity using p. ('*' sign is used to access value stored at that address)
    printf("%d\n", y);

    /* CHAIN OF POINTERS */
    int x, *p1, **p2;
    x = 100;
    p1 = &x; // Address of x
    p2 = &p1; // Address of p1
    printf("%d %d %d\n", x, *p1, **p2); // All prints 100 because of obvious reasons

    /* USE OF POINTERS IN EXPRESSIONS */
    int sum = *p1 + **p2; // Stores 200 in sum
    printf("%d\n", sum);

    // Note that we can not assign a constant value to pointer variables with an exception for NULL and 0.
    int *_p = 5000;
    printf("%u\n", *_p); // This will result into segmentation fault and dumping of the core.
    return 0;
}