#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main(void) {
    int fd = open("demo.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR); // Open file in Write only and if it does not exist then create the file.
    // Give permissions to the file. These include Read and write.
    if(fd == -1) // Error checking
    {
        perror("Exited!"); // Error in human readable form.
        exit(EXIT_FAILURE); // Exit with appropriate status code
    }
    if(write(fd, "", 1) == -1) // Simultaneously write and check for error in file.
    {
        perror("Exited write!");
        exit(EXIT_FAILURE);
    }
    close(fd); // Close the file.
    return 0;
}

/* 
    The touch works by opening the file in write mode and to change the modified time, write nothing in the file XD.
*/