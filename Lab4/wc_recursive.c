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
            char newBuf[BUFSIZ] = {0};
            snprintf(newBuf, BUFSIZ, "%s/%s", name, d->d_name);
            int fd = open(newBuf, O_RDONLY);
            if (fd == -1)
            {
                perror("File Open Error in recursion.");
                exit(EXIT_FAILURE);
            }
            int i, charCount = 0, lineCount = 0, wordCount = 0;
            char buf[BUFSIZ] = {0};
            while (i = read(fd, buf, 1) > 0)
            {
                charCount++;
                if (buf[0] == '\n')
                    lineCount++;
                if (buf[0] == ' ')
                    wordCount++;
            }
            char newBuf1[BUFSIZ] = {0};
            snprintf(newBuf1, BUFSIZ, "\nLines: %d\nWords: %d\nChar: %d\n\n", lineCount, wordCount, charCount);
            write(1, d->d_name, sizeof(char *));
            write(1, newBuf1, sizeof(newBuf1));
            close(fd);
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