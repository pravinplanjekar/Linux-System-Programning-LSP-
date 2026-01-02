/*
2. File Copy with Offset
Problem Statement:
Copy a file starting from a given byte offset of the source le.
Input:
source_file destination_file offset
Output:
Partial le copied starting from offset.
*/

#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>

#define SIZE_BUFFER 1024

int main(int argc, char *argv[])
{
    int fd1 = 0, fd2 = 0;
    char Buffer[SIZE_BUFFER];
    int iRet_Src = 0;
    int iRet_Dest = 0;
    struct stat sobj;
    int iRet = 0;
    off_t offset = 0;

/////////// ARGUMENT VALIDATION////////////////////////////////

    if (argc != 4)
    {
        printf("Invalid Arguments...\n");
        return -1;
    }
////////////////////////////////////////////////////////////////

    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[2],O_CREAT | O_WRONLY | O_TRUNC, 0777);

//////////////////FILE DETAILS AND PERMISSION CHECK////////////
    stat(argv[1], &sobj);
    chmod(argv[2], sobj.st_mode);

////////////////////////////////////////////////////////////////

    offset = (off_t)atol(argv[3]);

    iRet = lseek(fd1,offset,SEEK_SET);

    while((iRet_Src = read(fd1,Buffer, SIZE_BUFFER)) > 0)
    {
        iRet_Dest = write(fd2,Buffer, iRet_Src);
    }

    printf("Data sucessfully copied...\n");


    close(fd1);
    close(fd2);

    return 0;

}