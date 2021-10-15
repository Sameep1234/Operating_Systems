/* 
    AU1940049 Sameep Vani
    Mid-Sem Exam CSE332 Operating System Lab
*/

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// Set ll and ld to be long long int and long double respectively
#define ll long long int
#define ld long double

// Define struct for pipe later on
struct finalAns
{
    ll words;
    ll characters;
    ll lines;
};

int main(int argc, char *argv[])
{
    // If argument counter is not 3, then number of arguments are not correct and display error msg
    if (argc != 3)
    {
        char *str = "Incorrect number of arguments.\n";
        int x = write(1, str, strlen(str));
        if (x == -1)
        {
            // Print error in humand readable form
            perror("Error in argument count");
            // Exit with appropriate status code
            exit(EXIT_FAILURE);
        }
    }
    // Convert char to int using atof().
    int numberOfProcess = atof(argv[2]);

    // open file present in the argument
    FILE *fp = fopen(argv[1], "r");

    // Check for error while opening the file
    if (fp == NULL)
    {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // Seek to the end of the file. This means set the position of the file pointer to the end of file.
    ld tempVar = fseek(fp, 0, SEEK_END);
    
    // Check for error during the seek
    if(tempVar == -1)
    {
        perror("Parent Seek Error");
        exit(EXIT_FAILURE);
    }

    // ftell will return the file set at the end by fseek(). 
    ld fileLength = ftell(fp);

    // Calculate the offset requited per process
    long fileLengthPerProcess = fileLength / numberOfProcess;

    // Declare array for the required offset
    int startingPos[numberOfProcess];

    // Initialize the offset array
    for (int i = 0; i <= numberOfProcess - 1; i++)
    {
        startingPos[i] = i * fileLengthPerProcess;
    }

    // Close file as the pointer points to last position and that is not desirable
    fclose(fp);

    // Create n child of same parent
    //Declare pipe
    int pipefd[2];

    //Create pipe
    int status = pipe(pipefd);

    // Check for error while creating pipe
    if (status == -1)
    {
        perror("Pipe Creation failed");
        exit(EXIT_FAILURE);
    }

    // For loop for creating one layer of child process.
    for (int i = 0; i < numberOfProcess; i++)
    {
        // Create child process
        ll pid = fork();
        
        // Check for error while creating the process
        if (pid == -1)
        {
            perror("Error while creating child");
            exit(EXIT_FAILURE);
        }

        // For child process, its process id is 0 and hence any process that enters this if is the child process
        if (pid == 0)
        {
            // Close read end for the child as it is not required
            close(pipefd[0]);

            // Reopen file
            fp = fopen(argv[1], "r");

            if (fp == NULL)
            {
                perror("Error in opening file");
                exit(EXIT_FAILURE);
            }

            // Set the position upto the starting point. Note that we started from the starting of the file.
            int readStatus = fseek(fp, startingPos[i], 0);
            if (readStatus == -1)
            {
                perror("");
                printf("Seek Error [child] %d\n\n\n\n", getpid());
                exit(EXIT_FAILURE);
            }

            // Create object for the struct
            struct finalAns pCount;
            // Initialize its variables
            pCount.characters = 0;
            pCount.words = 0;
            pCount.lines = 0;
            for (int i = 0; i < fileLengthPerProcess; i++)
            {
                char temp = getc(fp);
                // printf("%c", temp);
                pCount.characters++;
                if (temp == '\n')
                {
                    pCount.lines++;
                }
                if (temp == ' ')
                {
                    pCount.words++;
                }
            }

            // Close file as its job is done for a particular child process
            fclose(fp);

            // Write the struct in the pipe and save it
            status = write(pipefd[1], &pCount, sizeof(pCount));
            if (status == -1)
            {
                perror("Error while writing in pipes");
                exit(EXIT_FAILURE);
            }

            // Close the write end of the child pipe
            close(pipefd[1]);

            // Terminate the child process
            exit(EXIT_SUCCESS);
        }
    }

    // Wait untill all the child processes are completed/terminated
    wait(NULL);
    close(pipefd[1]);

    // Object for the actual answer is created
    struct finalAns actualFinalAnswer;

    // Initialized the variables
    actualFinalAnswer.characters = 0;
    actualFinalAnswer.words = 0;
    actualFinalAnswer.lines = 0;

    // For loop for reading the contents of the pipe
    for (int i = 0; i < numberOfProcess; i++)
    {
        
        struct finalAns pCount;
        pCount.characters = 0;
        pCount.words = 0;
        pCount.lines = 0;
        // Read the contents of pipe and store it in pCount object of struct
        int readStatus = read(pipefd[0], &pCount, sizeof(struct finalAns));
        if (readStatus == -1)
        {
            perror("Error while reading from pipe");
            exit(EXIT_FAILURE);
        }

        // Calculate the final answer
        actualFinalAnswer.characters += pCount.characters;
        actualFinalAnswer.words += pCount.words;
        actualFinalAnswer.lines += pCount.lines;
    }

    char buf[BUFSIZ] = {0}; // Buffer array for storing the final answer.
    //Store final answer in buffer.
    snprintf(buf, BUFSIZ, "\n%lld %lld %lld\n", actualFinalAnswer.characters, actualFinalAnswer.words, actualFinalAnswer.lines);
    int finalWrite = write(1, buf, sizeof(buf)); // Print in stdout the final answer.
    if (finalWrite == -1)
    {
        perror("Error during final write");
        exit(EXIT_FAILURE);
    }
    
    close(pipefd[0]);
    return 0;
}