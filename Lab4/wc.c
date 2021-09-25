#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    int i,charCount = 0,fd, lineCount = 0, wordCount = 0;
    char buf[BUFSIZ];
    fd = open("demo.c", O_RDONLY);

    if(fd == -1)
    {
        perror("File Open Error (Read)");
        exit(1);
    }
    else
    {
        while(i=read(fd, buf, 1) > 0)
        {
            charCount++;
            if(buf[0] == '\n') lineCount++;
            if(buf[0] == ' ') wordCount++;
        }
    }
    char newBuf[BUFSIZ] = {0};
    snprintf(buf, BUFSIZ, "Lines: %d\nWords: %d\nChar: %d", lineCount, wordCount, charCount);
    write(1, newBuf, sizeof(newBuf));

    close(fd);
    return 0;
}