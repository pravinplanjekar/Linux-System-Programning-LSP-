/*
1. File Copy Utility
Problem Statement:
Write a program that copies the contents of one le into another.
Input:
Source le name and destination le name as command-line arguments.
Output:
Destination le containing an exact copy of source le.
•Handle le-not-found and permission errors.
•Destination le should be created if not present.
*/

#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>


#define SIZE_BUFFER 1024

int main(int argc, char *argv[])
{
    int fd1 = 0, fd2 = 0;
    char Buffer[SIZE_BUFFER];
    int iRet_Src = 0;
    int iRet_Dest = 0;
    struct stat sobj;

    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[2],O_CREAT | O_WRONLY | O_TRUNC, 0777);

    if (fd1 == -1)
    {
        perror("open");
        return -1;
    }


    stat(argv[1], &sobj);
    if(chmod(argv[2], sobj.st_mode) != 0)
    {
        perror("Permission");
        return -1;
    }

    while((iRet_Src = read(fd1,Buffer, SIZE_BUFFER)) > 0)
    {
        iRet_Dest = write(fd2,Buffer, iRet_Src);
    }

    printf("Data sucessfully copied...\n");


    close(fd1);
    close(fd2);

    return 0;

}