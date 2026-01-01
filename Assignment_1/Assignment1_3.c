/*
Check File Access Permission
•Accept le name and mode (read/write/execute).
•Use access() to check permission for current process.
•Print “Accessible / Not accessible” with reason.
*/

#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>


int main(int argc, char *argv[])
{
    int fd = 0;
    int flag = 0;

    
    if(strcmp(argv[2], "read") == 0 )
    {
        flag = R_OK;
    }
    else if(strcmp(argv[2], "write") == 0)
    {
        flag = W_OK;
    }
    else if(strcmp(argv[2], "execute")== 0)
    {
        flag = X_OK;
    }
    else if(strcmp(argv[2], "test")== 0)
    {
        flag = F_OK;
    }
    else
    {
        printf("Invalid Mode\n");
        return -1;
    }

    fd = access(argv[1],flag);

    if (fd == -1)
    {
        perror("Access");
        return -1;
    }
    else
    {
        printf("File is accessible\n");
    }

    
    close(fd);

    return 0;
}