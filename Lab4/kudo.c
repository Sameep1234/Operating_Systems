#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <string.h>

/* struct dirent
{
    long d_ino;
    off_t d_off;
    unsigned short d_reclen;
    unsigned char  d_type;
    char d_name[256];
}; */

void recursive(void *name)
{
    struct stat sfile;
    strcat(name, "/");
    strcat(name, d->d_name);
    int fd = open(name, O_RDONLY);
    if (fd == -1)
    {
        perror("Open Error in recursive function");
        exit(EXIT_FAILURE);
    }

    if (stat(name, &sfile) == -1)
    {
        perror("No Stat in recursive");
        exit(EXIT_FAILURE);
    }
    close(fd);
    for (struct dirent *d = readdir(name); d != NULL; d = readdir(name))
    {
        if(d->d_type & DT_DIR)
        {
            printf("%s\n", d->d_name);
            recursive(name);
        }
        else
        {
            printf("%s\n", d->d_name);
        }
    }
}

int main(void)
{
    struct stat sfile;
    void *path = "/home/sameep/Extra Projects/Operating_Systems/Lab4";
    int fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        perror("Open Error");
        exit(EXIT_FAILURE);
    }

    int temp = stat(path, &sfile);

    if (sfile.st_mode & S_IFDIR)
    {
        close(fd);
        recursive(path);
    }
    else
    {
        printf("It is a file");
    }

    return 0;
}

/* if (bpos < bytes)
    {
        strcat(name, d->d_name);
        int fd = open(name, O_RDONLY | O_DIRECTORY);
        if (fd == -1)
        {
            perror("File error!");
            exit(EXIT_FAILURE);
        }
        else
        {
            struct stat sfile;
            if (stat(name, &sfile) == -1)
            {
                perror("No Stat!");
                exit(EXIT_FAILURE);
            }
            else
            {
                printf("PATH: %s", name);
                if (sfile.st_mode & S_IFDIR)
                {
                    bpos += d->d_reclen;
                    printf("It is a directory %s", d->d_name);
                    recursive(name, bytes);
                }
                else
                {
                    bpos += d->d_reclen;
                    printf("It is a file %s", d->d_name);
                }
            }
        } */

/* int bpos;
    char buf[BUFSIZ] = {0};
    // struct stat sfile;
    while (bpos < bytes)
    {
        d = (struct dirent *)(buf + bpos);
        strcat(name, d->d_name);
        if (stat(name, &sfile) == -1)
        {
            perror("Stat Error!");
            exit(EXIT_FAILURE);
        }
        else
        {
            if (sfile.st_mode & S_IFDIR)
            {
                int fd = open(name, O_RDONLY | O_DIRECTORY);
                char buf[BUFSIZ] = {0};
                int bytes = syscall(SYS_getdents, fd, buf, BUFSIZ);
                printf("DIRECTORY: %s", d->d_name);
                recursive(name, bytes);
            }
            else
            {
                printf("FILE: %s", d->d_name);
            }
            bpos += d->d_reclen;
        }
    } */