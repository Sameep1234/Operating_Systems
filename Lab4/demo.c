#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

// Copy files program

/*Do the following
 Proper error handling
 Loop
 Recursive version
*/

int main(void)
{
    int fd = open("demo.txt", O_RDONLY);
    char buf[BUFSIZ] = {0};

    int num = read(fd, buf, BUFSIZ);

    int new_fd = open('copied_demo.txt', O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if(num == -1) {
        perror("read error");
        exit(1);
    }
    write(new_fd, buf, num);

    close(fd);
    close(new_fd);
    return 0;
}

// objdump -d open.out | less