// Author: @dhruvildave
// Sat Sep 25 12:30:21 PM IST 2021

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void
recurse(char *path)
{
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    for (struct dirent *dp = readdir(dir); dp != NULL; dp = readdir(dir)) {
        if (errno != 0) {
            perror("readdir");
            exit(EXIT_FAILURE);
        }

        // Check if . or .. to prevent unnecessary traversals
        if (strncmp(dp->d_name, ".", 1) == 0 ||
            strncmp(dp->d_name, "..", 2) == 0) {
            continue;
        }

        // Check if directory or not
        if (dp->d_type == DT_DIR) {
            // If directory then opendir into it
            char buf[BUFSIZ] = {0};
            snprintf(buf, BUFSIZ, "%s/%s", path, dp->d_name);
            recurse(buf);
        } else {
            // If not directory do whatever must be done
            printf("%s/%s\n", path, dp->d_name);
        }
    }

    closedir(dir);
}

int
main(void)
{
    recurse("/home/sameep/Extra Projects/Operating_Systems");

    return 0;
}
