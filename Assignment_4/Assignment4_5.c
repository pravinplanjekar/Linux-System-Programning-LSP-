/*
5. Reverse File Content
Problem Statement:
Display the contents of a file in reverse order.
Input:
File name.
Output:
File content printed in reverse.
*/

#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>


#define SIZE_BUFFER 1

int main(int argc, char *argv[])
{
    int fd1 = 0;
    char Buffer[SIZE_BUFFER];
    int iRet_Src = 0;
    int iRet_Dest = 0;
    struct stat sobj;
    off_t iRet = 0;
    off_t pos = 0;
    

/////////// ARGUMENT VALIDATION////////////////////////////////

    if (argc != 2)
    {
        printf("Invalid Arguments...\n");
        return -1;
    }
////////////////////////////////////////////////////////////////

    fd1 = open(argv[1], O_RDONLY);

    if (fd1 == -1)
    {
        perror("open");
        return -1;
    }


    if (fstat(fd1, &sobj) == -1)
    {
        printf("fstat failed: %s\n", strerror(errno));
        close(fd1);
        return -1;
    }
//////////////////////////REVERSE LOGIC////////////////////////////////////////  
    iRet = lseek(fd1,-1,SEEK_END);
    printf("Updated file offset is : %ld\n",iRet);

    pos = sobj.st_size-1;

    while(pos >= 0 )
    {
        lseek(fd1, pos, SEEK_SET);
        iRet_Src = read(fd1,Buffer, SIZE_BUFFER);
        iRet_Dest = write(1,Buffer, SIZE_BUFFER);
        pos--;
        
    }
    printf("\n");
/////////////////////////////////////////////////////////////////////////////////

    close(fd1);

    return 0;

}