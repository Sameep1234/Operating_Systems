#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void)
{
    int x = fork(); // Creates child process. After this, all the code inside this process will be copied by the child.
    int y = '123'; // After fork, this will be in both stacks (child and process).
    // Returns the process id of child to parent. So for child, the process id is 0 and for parent it is x
    // NOTE THAT THE CHILD PROCESS ID WILL ALWAYS BE 0.
    /*
        Copied part: Stack, PCB, Code. Hence value of x is stored in both child and process.
    */
    printf("%d\n", x);
    if(x == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if(x == 0) {
        y++; // This will change value of y only in child's stack and not in parent's stack.
        printf("Only in child"); // Prints only for child (access only to child)
        printf("Child Process id: %d", getpid()); // This will not be 0 but returns its original process id.
        // NOTE THAT THE X WILL ALWAYS BE 0.
        printf("Parent Process id: %d", getppid());// This will be the process id of parent.
        while(1) {

            
        }
    } else {
        printf("%d\n", 4); // Prints only for parent (access only to parent process)
    }

    wait(NULL); // Wait untill all the child process are completed
    printf("[%d] runs in both", getpid()); // Prints 2 times (for child and for parent)
    return 0;
}