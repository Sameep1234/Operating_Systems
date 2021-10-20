/*
    C program to implement 3 processes (ps, grep and wc)
    Communicate amongst these processes using system calls
        These include pipe, any of exec family, fork, write, read, wait, open, close etc.

    Flow: You have to run the file from where the 2 processes will be called and aoutput of ps will be redirected to
    grep / wc command which will return a tabular output containing the process details of matching process status
    or the line counts/word counts of the processes tables.

    ./a.out ps grep <status> --> Status includes either of the statuses of the processes
    ./a.out ps wc < l \ w \ c > --> Self explanatory


    MY FLOW:
    Parent will contain code for "ps". It will have a child process based on arguments passed. Through pipes, the result of
    "ps" would be stored in a file which is also accessible to child which in turn will perform operations based on arguments
    passed (either wc or grep). Further, the parent will collect the result and print the final answer.
*/

#include <dirent.h>      // Includes directory related system calls
#include <fcntl.h>       // Includes basic files related system calls
#include <stdio.h>       // Includes basic library calls
#include <unistd.h>      // Includes fork like system calls
#include <stdlib.h>      // Includes BUFSIZ (buffer size)
#include <sys/stat.h>    // Need this for directory based system calls
#include <sys/syscall.h> // Includes basic system calls
#include <sys/types.h>   // Includes basic system calls
#include <sys/wait.h>    // Includes time functionalities like ctime etc.
#include <string.h>      // Includes string functionalities like compare and append

void handleError(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    // Check whether the correct number of arguments are passed or not.
    if (argc != 4)
        handleError("Incorrect number of arguments!");

    /*
        system() executes the command written in it
        store the output of "ps" in temp.txt using "cat" command
    */
    if (system("ps | cat >> temp.txt") == -1)
        handleError("system() error");

    int pipefd[2];          // Declare pipes
    if (pipe(pipefd) == -1) // Create pipe
        handleError("Creation of pipe failed");

    if (strcmp(argv[2], "wc") == 0)
    {
        // Need to pass the output of ps into wc

        int id = fork(); // Create child process
        if (id == -1)
            handleError("Creation of child process failed");
        else if (id == 0)
        {
            /* CHILD PROCESS */
            close(pipefd[0]); // Close the read end of the child pipe as it is not required.

            // Open temp.txt which containts output of "ps" command
            int fd = open("temp.txt", O_RDONLY);
            if (fd == -1)
                handleError("[wc] File open failed");

            char buf; // Create and initilize buffer to store contents of temp.txt            
            int count[3] = {0};
            // Declare and initialize an array to store line count, word count and character count
            /*
                0th index represents charaters
                1st index represents words
                2nd index represents lines
            */
            
            // Code for wc
            while (read(fd, &buf, 1) > 0)
            {
                count[0]++;
                if (buf == '\n')
                    count[2]++;
                if (buf == ' ')
                    count[1]++;
            }

            // Write the array to pipe
            if(write(pipefd[1], count, sizeof(count)) == -1)
                handleError("[wc] Writing to pipe failed");
            
            // Close temp.txt
            if(close(fd) == -1)
                handleError("[wc] Closing of file failed");
        }
    }
    else
    {
        // Need to pass the output of ps to grep

        int id = fork(); // Create child process
        if (id == -1)
            handleError("Creation of child process failed");
        else if (id == 0)
        {
            /* CHILD PROCESS */

            close(pipefd[0]); // Close the read end of the child pipe as it is not required.
        }
    }

    close(pipefd[1]); // Close the write end of both parent and child.

    wait(NULL); // Parent will wait untill all the child processes are completed.
    
    // Declare an array of final answer
    int finalAns[3];
    
    // Read from pipe and store it into finalAns array
    if(read(pipefd[0], finalAns, sizeof(finalAns)) == -1)
        handleError("[Parent] Read from pipe failed");
    
    // Print the final ans
    printf("%d %d %d \n", finalAns[0], finalAns[1], finalAns[2]);
    
    // Run actual wc command for comparing values
    if(system("wc temp.txt") == -1)
        handleError("wc command failed");
    
    // Delete the previously created temp.txt file
    unlink("temp.txt");
    return 0;
}