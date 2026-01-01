/*
Open File in Given Mode
•Accept le name and mode (R, W, RW, A) from user.
•Convert mode to ags (O_RDONLY, O_WRONLY, O_RDWR, O_APPEND | O_CREAT).
•Open file accordingly and display fd.
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

    

    if(strcmp(argv[2], "R") == 0 )
    {
        flag = O_RDONLY;
    }
    else if(strcmp(argv[2], "W") == 0)
    {
        flag = O_WRONLY | O_CREAT;
    }
    else if(strcmp(argv[2], "RW")== 0)
    {
        flag = O_RDWR | O_CREAT;
    }
    else if(strcmp(argv[2], "A"))
    {
        flag = O_WRONLY | O_CREAT | O_APPEND;
    }

    fd = open(argv[1],flag, 0777);

    if (fd == -1)
    {
        perror("open");
        return -1;
    }

    printf("File opened successfully with fd : %d\n", fd);
    
    close(fd);

    return 0;
}