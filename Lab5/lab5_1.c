#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int pipefd[2] = {0}; // Array of pipe file descriptor (0 for read side and 1 for write side)
    pipe(pipefd); // Create the pipe for the parent process.
    int x = fork();

    printf("Child process id: %d\n", x);

    printf("pipe fd: [%d] and [%d]", pipefd[0], pipefd[1]); // Just printing the file descriptor of the two files of the process.

    if (x == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (x == 0)
    {
        close(pipefd[0]);
        /* Since we do not need the read functionalilty, we are closing the read part of the child file pointer pipe. */
        int something = 29304809; // Declaring and initializing integer type to be read on parent side (read) of the pipe.

        write(pipefd[1], &something, sizeof(int)); // Write the variable into write end of the pipe.

        close(pipefd[1]); // Close the write end of the file pointer.
        exit(EXIT_SUCCESS);
        /* 
            EXIT IS IMPORTANT BECAUSE IF WE DONT DO IT THEN THE CHILD WILL EXECUTE THE CODE FOR READ BELOW.
            THEN FOR THE PARENT TO READ, THERE IS NO DATA IN THE WRITE END OF THE PIPE.
            THUS THE PARENT'S READ WILL WAIT FOR THE DATA AND GO INTO GARBAGE STATE. 
        */
    }
    char buf[BUFSIZ] = {0};
    int something_rec = 0;
    read(pipefd[0], &something_rec, sizeof(int));
    printf("[%d] %d\n", x, something_rec);

    wait(NULL);

    // close the read end
    close(pipefd[0]);

    // close the write end
    close(pipefd[1]);

    return 0;
}