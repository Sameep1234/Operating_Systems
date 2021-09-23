#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main(void) {
    int fd = open("demo.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if(fd == -1)
    {
        perror("Exited!");
        exit(EXIT_FAILURE);
    }
    if(write(fd, "", 1) == -1)
    {
        perror("Exited write!");
        exit(EXIT_FAILURE);
    }
    close(fd);
    return 0;
}