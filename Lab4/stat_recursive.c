#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
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
            write(1, d->d_name, strlen(d->d_name));          // Print the directory name in stdout.
            struct stat sfile;                               // Create variable of struct stat data type.
            char buf[BUFSIZ];                                // Create buffer array for appending new path.
            snprintf(buf, BUFSIZ, "%s/%s", name, d->d_name); // Append new path.
            if (stat(buf, &sfile) == -1)                     // Check for errors in "stat" system call.
            {
                perror("No Stat!"); // Error in human readable form
                exit(EXIT_FAILURE); // Exit with appropriate failure
            }
            else
            {
                char buf[BUFSIZ] = {0}; // Buffer array for storing the final answer.
                //Store final answer in buffer.
                snprintf(buf, BUFSIZ, "\nPermissions (User): %c%c%c\nsize: %ld\nblocks: %ld\nIO Block: %ld\nDevice: %lu\nInode: %lu\nLinks: %lu\nUid: %d\nGid: %d\nAccess: %s\nModify: %s\nStatus Change: %s\n", (sfile.st_mode & S_IRUSR) ? 'r' : '-', (sfile.st_mode & S_IWUSR) ? 'w' : '-', (sfile.st_mode & S_IXUSR) ? 'x' : '-', sfile.st_size, sfile.st_blocks, sfile.st_blksize, sfile.st_dev, sfile.st_ino, sfile.st_nlink, sfile.st_uid, sfile.st_gid, ctime(&sfile.st_atime), ctime(&sfile.st_mtime), ctime(&sfile.st_ctime));
                write(1, buf, sizeof(buf)); // Print in stdout the final answer.
            }
        }
    }
}

int main(void)
{
    // THE FOLLOWING CODE DOES NOT HAVE COMMENTS BECAUSE IT IS ALMOST SIMILAR TO WC WITH A BIT MODIFICATION.
    struct stat sfile;
    char *path = "/home/sameep/Extra Projects/Operating_Systems/Lab4";
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
        write(1, path, strlen(path));
        struct stat sfile;
        if (stat(path, &sfile) == -1)
        {
            perror("No Stat!");
            exit(EXIT_FAILURE);
        }
        else
        {
            char buf[BUFSIZ] = {0};
            snprintf(buf, BUFSIZ, "\nPermissions (User): %c%c%c\nsize: %ld\nblocks: %ld\nIO Block: %ld\nDevice: %lu\nInode: %lu\nLinks: %lu\nUid: %d\nGid: %d\nAccess: %s\nModify: %s\nStatus Change: %s\n", (sfile.st_mode & S_IRUSR) ? 'r' : '-', (sfile.st_mode & S_IWUSR) ? 'w' : '-', (sfile.st_mode & S_IXUSR) ? 'x' : '-', sfile.st_size, sfile.st_blocks, sfile.st_blksize, sfile.st_dev, sfile.st_ino, sfile.st_nlink, sfile.st_uid, sfile.st_gid, ctime(&sfile.st_atime), ctime(&sfile.st_mtime), ctime(&sfile.st_ctime));
            write(1, buf, sizeof(buf));
        }
    }

    return 0;
}