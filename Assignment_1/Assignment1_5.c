/*
Read N Bytes From File
•Accept file name and number of bytes N.
•Read exactly N bytes using read() and print on console.
•If le contains less than N, print only available bytes
*/

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include <stdlib.h>

#define SIZE_BUFFER 100

int main(int argc, char *argv[])
{
    int fd = 0;
    char Buffer[SIZE_BUFFER];
    int iRet = 0;
    int N = atoi(argv[2]);

    memset(Buffer,'\0',SIZE_BUFFER);

    if (N > SIZE_BUFFER)
    N = SIZE_BUFFER;

    fd = open(argv[1],O_RDONLY);
    
    if(fd < 0)
    {
        printf("Unable to open the file\n");
        printf("Reson : %s\n",strerror(errno));
        return -1;
    }

    printf("File succesfully opened with fd : %d\n",fd);

    iRet = read(fd, Buffer, N);       

    printf("%d bytes gets succesfully read\n",iRet);

    printf("Data from file  : %s\n",Buffer);

    close(fd);

    return 0;
}