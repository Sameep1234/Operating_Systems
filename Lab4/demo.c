#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main(void)
{
    int x = open("demo.txt", O_RDONLY);
    close(x);
    return 0;
}

// objdump -d open.out | less