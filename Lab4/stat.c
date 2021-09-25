#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
    struct stat sfile;
    const char *fileName = "/home/sameep/Extra Projects/Operating_Systems/Lab4/demo.c";
    int fd = open(fileName, O_RDONLY);
    if (fd == -1)
    {
        perror("File did not open!");
        exit(EXIT_FAILURE);
    }
    if (stat(fileName, &sfile) == -1)
    {
        perror("No Stat!");
        exit(EXIT_FAILURE);
    }
    else
    {
        char buf[BUFSIZ] = {0};
        snprintf(buf, BUFSIZ, "size: %ld\nblocks: %ld\nIO Block: %ld\nDevice: %lu\nInode: %lu\nLinks: %lu\nUid: %d\nGid: %d\nAccess: %s\nModify: %s\nStatus Change: %s\n", sfile.st_size, sfile.st_blocks, sfile.st_blksize, sfile.st_dev, sfile.st_ino, sfile.st_nlink, sfile.st_uid, sfile.st_gid, ctime(&sfile.st_atime), ctime(&sfile.st_mtime), ctime(&sfile.st_ctime));
        write(1, buf, sizeof(buf));
    }
    close(fd);
    return 0;
}