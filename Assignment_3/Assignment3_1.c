/*
Copy File Contents (source → destination)
•Accept source_file and dest_file.
•Create destination if not exists (O_CREAT | O_TRUNC).
•Copy using buffered read()/write() loop.
•Preserve permissions (optional bonus using stat() + chmod()).
*/

#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<dirent.h>
#include<sys/types.h>

#define SIZE_BUFFER 1024

int main(int argc, char *argv[])
{
    int fd1 = 0, fd2 = 0;
    char Buffer[SIZE_BUFFER];
    int iRet_Src = 0;
    int iRet_Dest = 0;
    struct stat sobj;

    fd1 = open(argv[1], O_RDONLY | O_APPEND);
    fd2 = open(argv[2],O_CREAT | O_WRONLY | O_TRUNC, 0777);

    stat(argv[1], &sobj);
    chmod(argv[2], sobj.st_mode);

    while((iRet_Src = read(fd1,Buffer, SIZE_BUFFER)) > 0)
    {
        iRet_Dest = write(fd2,Buffer, iRet_Src);
    }

    printf("Data sucessfully copied...\n");


    close(fd1);
    close(fd2);

    return 0;

}