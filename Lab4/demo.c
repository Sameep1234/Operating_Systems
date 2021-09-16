#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

// Copy files program

int main(void)
{
    int fd = open("demo.txt", O_RDONLY);
    char buf[BUFSIZ] = {0};

    read(fd, buf, BUFSIZ);

    int new_fd = open('copied_demo.txt', O_WRONLY | O_CREAT);
    write(new_fd, buf, BUFSIZ);

    close(fd);
    close(new_fd);
    return 0;
}

// objdump -d open.out | less