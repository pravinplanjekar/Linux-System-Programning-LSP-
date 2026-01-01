/*
Display Complete File Information
Accept le name and display le metadata using stat():
• Size, inode, permissions, hard links, owner uid/gid, flle type, last access/modify time.
*/

#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>


int main(int argc, char *argv[])
{
    struct stat sobj;
    int iRet = 0;
    

    iRet = stat(argv[1],&sobj);

    if (iRet == -1)
    {
        perror("Open");
        return -1;
    }
    else
    {
        printf("Total Size : %ld\n",sobj.st_size);
        printf("Inode Number : %ld\n",sobj.st_ino);
        printf("Permission : %d\n",sobj.st_mode);
        printf("Hardlink count :%ld\n",sobj.st_nlink);
        printf("Ownership :%d\n",sobj.st_uid);
        printf("Ownership :%d\n",sobj.st_gid);
        printf("Last File Access : %ld\n",sobj.st_atime);
        printf("Last File Modification : %ld\n",sobj.st_mtime);

    }

    
    close(iRet);

    return 0;
}