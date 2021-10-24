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
    int x[5] = {1, 2, 3, 4, 5}; // Continuous block of memory is created
    int *p = &x[0]; // If we know this, we know the address of all the elements as it is a continuous block.
    printf("%d\n", p);

    /* STRINGS */
    char *str = "good"; // This points to the first char i.e g and not to the whole word.
    printf("%s\n", str);

    /* Array of pointers (chain of pointers concept) */
    char *name[3] = {"New Zealand", "Australia", "India"};
    for(int i = 0;i<3;i++)
    {
        printf("%s ", name[i]);
        if(i == 2)
            printf("\n");
    }

    return 0;
}