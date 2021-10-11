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
    while ((d = readdir(temp)) != NULL)
    {
        if (strncmp(d->d_name, ".", 1) == 0 ||
            strncmp(d->d_name, "..", 2) == 0)
        {
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
            char buf[BUFSIZ] = {0};
            snprintf(buf, BUFSIZ, "%s/%s", name, d->d_name);
            const char *dest = "/home/sameep/Extra Projects/Operating_Systems/destination";
            char newBuf[BUFSIZ] = {0};
            snprintf(newBuf, BUFSIZ, "%s/%s", dest, d->d_name);

            int fd0 = 0;
            if ((fd0 = open(buf, O_RDONLY)) == -1)
            {
                const char *str = "to copy";
                write(2, str, strlen(str)); // 2 is for standard error
                exit(1);
            }

            int fd1 = 0;
            if ((fd1 = open(newBuf, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
            {
                perror("destination");
                exit(1);
            }

            for (int err = read(fd0, buf, BUFSIZ); err != -1;
                 err = read(fd0, buf, BUFSIZ))
            {
                if (err == 0)
                {
                    break;
                }

                if (write(fd1, buf, err) == -1)
                {
                    perror("write");
                }
            }

            unlink(buf);

            close(fd0);
            close(fd1);
        }
    }
}

int main(void)
{
    struct stat sfile;
    char *path = "/home/sameep/Extra Projects/Operating_Systems/Lab4/move";
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
        int fd0 = 0;
        char buf[BUFSIZ] = {0};
        const char *dest = "/home/sameep/Extra Projects/Operating_Systems/destination";

        if ((fd0 = open(buf, O_RDONLY)) == -1)
        {
            const char *str = "to copy";
            write(2, str, strlen(str)); // 2 is for standard error
            exit(1);
        }

        int fd1 = 0;
        if ((fd1 = open(dest, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
        {
            perror("destination");
            exit(1);
        }

        for (int err = read(fd0, buf, BUFSIZ); err != -1;
             err = read(fd0, buf, BUFSIZ))
        {
            if (err == 0)
            {
                break;
            }

            if (write(fd1, buf, err) == -1)
            {
                perror("write");
            }
        }

        unlink(buf);

        close(fd0);
        close(fd1);
    }

    return 0;
}