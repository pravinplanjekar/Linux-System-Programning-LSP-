/*
3. File Copy Using pread & pwrite
Problem Statement:
Copy a file using pread() and pwrite() without changing the file offset.
Input:
Source and destination file names.
Output:
Copied file identical to source.
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
    int iRet1 = 0;
    off_t offset = 0;

/////////// ARGUMENT VALIDATION////////////////////////////////

    if (argc != 4)
    {
        printf("Invalid Arguments...\n");
        return -1;
    }
////////////////////////////////////////////////////////////////

    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0777);

//////////////////FILE DETAILS ////////////////////////////////

    stat(argv[1], &sobj);
    
////////////////////////////////////////////////////////////////

    offset = (int)atol(argv[3]);

    iRet1 = lseek(fd1,0,SEEK_SET);

    printf("Current offset before writing a file : %d\n", iRet1);  //0

    while((iRet_Src = pread(fd1,Buffer, SIZE_BUFFER,offset)) > 0)
    {
        iRet_Dest = pwrite(fd2,Buffer, iRet_Src,0);
        offset += iRet_Dest;
    }

    printf("Data sucessfully copied...\n");

    printf("Current offset after writing a file : %d\n", iRet1);  //0

    close(fd1);
    close(fd2);

    return 0;

}