/*
List Files with Type
•Accept directory name.
•Print each entry with its type: Regular / Directory / Link / FIFO / Socket / Char / Block
•Use lstat() for accurate type.
*/

#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>

int main(int argc, char *argv[])
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    struct stat sobj;
    char path[1024];

    dp = opendir(argv[1]);

    if(dp == NULL)
    {
        printf("%s\n",strerror(errno));
        return -1;
    }

    while(ptr = readdir(dp))
    {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;

        
        //printf("File name : %s\n",ptr->d_name);

        snprintf(path, sizeof(path),"%s/%s", argv[1], ptr-> d_name);

        if (stat(path, &sobj) == -1)
            continue;
        
        if(S_ISBLK(sobj.st_mode))
        {
            printf("File Name : %s | Type : Block Device", ptr->d_name);
        }
        else if(S_ISCHR(sobj.st_mode))
        {
            printf("File Name : %s | Type : Character Device\n", ptr->d_name);
        }
        else if(S_ISDIR(sobj.st_mode))
        {
            printf("File Name : %s | Type : Directory File\n", ptr->d_name);

        }
        else if(S_ISREG(sobj.st_mode))
        {
            printf("File Name : %s | Type : Regular File\n", ptr->d_name);
        }
        else if(S_ISSOCK(sobj.st_mode))
        {
            printf("File Name : %s | Type : Socket File\n", ptr->d_name);
        }
        else if(S_ISFIFO(sobj.st_mode))
        {
            printf("File Name : %s | Type : Pipe File\n", ptr->d_name);
        }
        else if(S_ISLNK(sobj.st_mode))
        {
            printf("File Name : %s | Type : Symbolic Link\n", ptr->d_name);
        }

    }

    
        

    closedir(dp);

    return 0;
}