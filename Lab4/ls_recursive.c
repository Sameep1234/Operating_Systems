#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <string.h>

void recursive(char *name)
{
    DIR *temp = opendir(name);
    struct dirent *d;
    while((d=readdir(temp)) != NULL)
    {
        if (strncmp(d->d_name, ".", 1) == 0 ||
            strncmp(d->d_name, "..", 2) == 0) {
            continue;
        }

        if (d->d_type & DT_DIR)
        {
            // printf("FULL PATH: %s\n", d->d_name);
            char buf[BUFSIZ] = {0};
            snprintf(buf, BUFSIZ, "%s/%s", name, d->d_name);
            // printf("BUF: %s", buf);
            recursive(buf);
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
    char *path = "/home/sameep/Extra Projects/Operating_Systems";
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
        char buf[BUFSIZ] = {0};
        snprintf(buf, BUFSIZ, "%s", path);
        write(1, buf, sizeof(buf));
    }

    return 0;
}