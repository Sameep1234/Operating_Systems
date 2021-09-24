#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
    struct stat sfile;
    const char *fileName = "/home/sameep/Extra Projects/Operating_Systems/Lab4";
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
        if(sfile.st_mode & S_IFDIR)
        {
            printf("It is a directory");
        }
        else 
        {
            printf("It is a file");
        }
        // printf("\nFile st_uid %d \n", sfile.st_uid);
        // printf("\nFile st_blksize %ld \n", sfile.st_blksize);
        // printf("\nFile st_gid %d \n", sfile.st_gid);
        // printf("\nFile st_blocks %ld \n", sfile.st_blocks);
        // printf("\nFile st_size %ld \n", sfile.st_size);
        // printf("\nFile st_nlink %u \n", (unsigned int)sfile.st_nlink);
        // printf("\nFile Permissions User\n");
        // printf("%c", sfile.st_mode);
        // printf((sfile.st_mode & S_IWUSR) ? "w" : "-");
        // printf((sfile.st_mode & S_IXUSR) ? "x" : "-");
        // printf("\n");
        // printf("\nFile Permissions Group\n");
        // printf((sfile.st_mode & S_IRGRP) ? "r" : "-");
        // printf((sfile.st_mode & S_IWGRP) ? "w" : "-");
        // printf((sfile.st_mode & S_IXGRP) ? "x" : "-");
        // printf("\n");
        // printf("\nFile Permissions Other\n");
        // printf((sfile.st_mode & S_IROTH) ? "r" : "-");
        // printf((sfile.st_mode & S_IWOTH) ? "w" : "-");
        // printf((sfile.st_mode & S_IXOTH) ? "x" : "-");
        // printf("\n");
    }

    // printf("st_mode = %lo", sfile.st_ino);
    return 0;
}