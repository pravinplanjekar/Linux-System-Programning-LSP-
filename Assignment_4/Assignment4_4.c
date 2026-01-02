/*
4. Problem Statement:
Merge multiple input les into a single output le.
Input:
output_file file1 file2 file3 ...
Output:
Combined file content in order.
*/

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>


#define SIZE_BUFFER 1024

int main(int argc, char *argv[])
{

    int i = 0;
    int fd_Output = 0;
    int fd = 0;
    int iRet = 0;
    char Buffer[SIZE_BUFFER];
    int iRet_Src = 0;
    int iRet_Dest = 0;

    if (argc <= 2)
    {
        printf("Invalid Arguments...\n");
        return -1;
    }

    fd_Output = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);


    for(i = 2; i < argc; i++)
    {
        fd = open(argv[i],O_RDONLY);

        while((iRet_Src = read(fd,Buffer, SIZE_BUFFER)) > 0)
        {
            iRet_Dest = write(fd_Output,Buffer, iRet_Src);
            
            //printf("%s file successfully copied...\n",argv[i]);
  
        }

        close(fd);

    }


    close(fd_Output);

    return 0;
}