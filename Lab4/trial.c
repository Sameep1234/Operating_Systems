#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/syscall.h>
#include <string.h>

int main()
{
    struct stat sfile;

    const char *filename = "/home/parth/Desktop/Code/OS-Labs/Lab4/mv/mv-nonrecursive.c";

    if (stat(filename, &sfile) == -1)
    {
        printf("Error Occurred\n");
    }
    char buf[BUFSIZ]={0};
    snprintf(buf, BUFSIZ, "\nPermissions (User): %c%c%c\nsize: %ld\nblocks: %ld\nIO Block: %ld\nDevice: %lu\nInode: %lu\nLinks: %lu\nUid: %d\nGid: %d\nAccess: %s\nModify: %s\nStatus Change: %s\n", (sfile.st_mode & S_IRUSR) ? 'r' : '-', (sfile.st_mode & S_IWUSR) ? 'w' : '-', (sfile.st_mode & S_IXUSR) ? 'x' : '-', sfile.st_size, sfile.st_blocks, sfile.st_blksize, sfile.st_dev, sfile.st_ino, sfile.st_nlink, sfile.st_uid, sfile.st_gid, ctime(&sfile.st_atime), ctime(&sfile.st_mtime), ctime(&sfile.st_ctime));
    write(1, buf, sizeof(buf));
}