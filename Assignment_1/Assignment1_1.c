/*
Open File
•Accept le name from user and open it using open().
•Print: success message + returned le descriptor.
•Handle errors using perror().
*/

#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>


int main(int argc, char *argv[])
{
    int fd = 0;

    fd = open(argv[1], O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return -1;
    }

    printf("File opened successfully with fd : %d\n", fd);
    
    close(fd);

    return 0;
}