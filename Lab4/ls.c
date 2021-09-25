#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>

struct linux_dirent
{
    long d_ino;
    off_t d_off;
    unsigned short d_reclen;
    char d_name[];
};

int main(int argc, char *argv[])
{
    int fd, bytes;
    char buf[BUFSIZ];
    struct linux_dirent *d;
    int bpos = 0;
    
    fd = open(argc > 1 ? argv[1] : ".", O_RDONLY | O_DIRECTORY);
    if (fd == -1)
        perror("open");

    bytes = syscall(SYS_getdents, fd, buf, BUFSIZ);
    if (bytes == -1)
        perror("getdents");

    while(bpos < bytes)
    {
        d = (struct linux_dirent *)(buf + bpos);
        printf("%s\n", d->d_name);
        bpos += d->d_reclen;
    }

    exit(EXIT_SUCCESS);
}