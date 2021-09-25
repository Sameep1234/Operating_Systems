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
    DIR *temp = opendir(name); // opendir system call will return a DIR (data type) pointer and thus is saved in temp.
    struct dirent *d; // Define a variable of struct dirent data type.
    /* 
        struct dirent is the data type which readdir system call returns. It is automaticallt updated with the directory entried of the directory opened in the previos code.
        Thus, it is requied to save the directory contents.
    */
    while ((d = readdir(temp)) != NULL) // Simultaneously check and store the value of returned by readdir system call.
    {
        /* 
            The below if conditions are required to check for parent directories and current directories.
            If the below code is not present then the code will be stuck on one file and might result into segmentation fault.
        */
        if (strncmp(d->d_name, ".", 1) == 0 ||
            strncmp(d->d_name, "..", 2) == 0)
        {
            continue;
        }

        if (d->d_type & DT_DIR) // Check whether the new directory entry is a directory of not.
        {
            char buf[BUFSIZ] = {0}; // Create buffer for appending/concatinating the new path.
            snprintf(buf, BUFSIZ, "%s/%s", name, d->d_name); // Concat and store the new path in the newly created buffer.
            recursive(buf); // Pass this new path as the parameter in the recursive function.
        }
        else
        {
            char newBuf[BUFSIZ] = {0};
            snprintf(newBuf, BUFSIZ, "%s/%s", name, d->d_name);
            int fd = open(newBuf, O_RDONLY); // Since it is a file, open the file in read only mode.
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
    /* 
        struct stat is the data type in which "stat" system call stores the values required.
        Thus, declare a variable of this file named sfile.
    */
    struct stat sfile;
    char *path = "/home/sameep/Extra Projects/Operating_Systems"; // Path for recursively doing word count.

    int temp = stat(path, &sfile); // Using stat system call which returns exit code for success(0) and failure(1).
    if (temp == -1)
    {
        perror("Stat Open Error"); // Prints error in human readable form.
        exit(EXIT_FAILURE);        // Exit with an appropriate status call.
    }

    if (sfile.st_mode & S_IFDIR) // Checks if the given path is a directory of not.
    {
        recursive(path); // If directory, send it to the recursive function with path as the parameter.
    }
    else
    {
        char buf[BUFSIZ] = {0};            // Declare and Initialize a buffer array.
        snprintf(buf, BUFSIZ, "%s", path); // Store the path in this buffer array.
        write(1, buf, sizeof(buf));        // Writes the output to the standard output as its file descriptor is 1.

        int fd = open(path, O_RDONLY); // Open the file and save the file descriptor.
        if (fd == -1) // Check for error
        {
            perror("File Open Error in recursion.");
            exit(EXIT_FAILURE);
        }
        int i, charCount = 0, lineCount = 0, wordCount = 0; // Declare and initialize the required variables.
        char buf[BUFSIZ] = {0}; // Create buffer array for storing values generated using the read system call.
        while (i = read(fd, buf, 1) > 0) // Simultaneously store and check for either EOF or errors. NOTE THAT HERE "1" JUST REPRESENTS TO READ 1 BYTE I.E ONE CHARACTER AT A MOMENT.
        {
            charCount++; // For each char read, increament the counter.
            if (buf[0] == '\n') // Condition for checking line or not.
                lineCount++; // Increament the line counter.
            if (buf[0] == ' ') // Condition for checing a word or not.
                wordCount++; // Increament the word counter.
        }
        char newBuf1[BUFSIZ] = {0}; // Create a new buffer for storing the final output.
        snprintf(newBuf1, BUFSIZ, "\nLines: %d\nWords: %d\nChar: %d\n\n", lineCount, wordCount, charCount); // Store the final output in the required format in the new buffer created.
        write(1, newBuf1, sizeof(newBuf1));// Write to the stdout the values stored in the new buffer.
        close(fd);//Close the opened file.
    }

    return 0;
}

/* 
    HOW DOES THE RECURSION WORK?
    Firstly, check whether the entered path is a file or directory. If it is a file then perform wc actions on it, else call recursive function.
    In the recursive function, we first open the directory using opendir system call.
    This returns a DIR (data type) pointer. Then a variable of struct dirent is declared named d.
    Then in the while loop, we initialize that variable(d) using readdir system call. Simultaneously check whether there is not an error.
    Then check for the discrepancies in the parent and current directory using the if statements.
    Then check whether the sent parameter is a directory of not.
    If it is a directory then using snprintf create a new path (which is essentially the concat of old path and current directory) and store it in a buffer array.
    Finally pass it in the next recursive call.
    If it is not a directory, then execute the wc code and we will get the required output.
*/