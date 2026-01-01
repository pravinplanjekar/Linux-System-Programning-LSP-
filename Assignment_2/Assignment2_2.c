/*
Write String to File
• Accept file name and a string from user
• Write string using write() (append mode)
• Print number of bytes written
*/

#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>


int main(int argc, char *argv[])
{
    int fd = 0;
    ssize_t iRet = 0;
    const char *filename = NULL;
    const char *data = NULL;

    fd = open(argv[1],O_WRONLY | O_APPEND);

    if (fd == -1)
    {
        perror("open");
        return -1;
    }

    filename = argv[1];
    data = argv[2];

    printf("File sucessfully opened with fd = %d\n",fd);

    iRet = write(fd, data, strlen(data));

    printf("%ld bytes gets sucessfully written\n",iRet);

    close(fd);

    return 0;

}