/*
Read Whole File
•Accept file name and print full content on console.
•Use a buffer loop (read() until 0).
•Show total bytes read.
*/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int fd = 0;
    char buffer[BUFFER_SIZE];
    int iRet = 0;
    ssize_t TotalBytes = 0;

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        printf("Unable to open file\n");
        printf("Reason: %s\n", strerror(errno));
        return -1;
    }

 
    while ((iRet = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        //write(STDOUT_FILENO, buffer, iRet);         shows all read data on console
        TotalBytes += iRet;
    }

    if (iRet < 0)
    {
        printf("\nRead error\n");
        printf("Reason: %s\n", strerror(errno));
        close(fd);
        return -1;
    }

    printf("\nTotal bytes read: %ld\n", TotalBytes);

    close(fd);
    return 0;
}
