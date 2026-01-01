/*
Find Largest File in Directory
•Accept directory name.
•Find and print:
◦largest le name
◦its size in bytes
Consider only regular files (ignore directories).
*/

#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>

#define SIZE_BUFFER 1024

int main(int argc, char *argv[])
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    struct stat sobj;
    char path[1024];
    char Buffer[SIZE_BUFFER];
    int iRet = 0;
    int fd = 0;
    long int iMax = 0;
    long int Large_iMax = 0;
    char *Large_fileName = NULL;

    dp = opendir(argv[1]);

    if(dp == NULL)
    {
        printf("%s\n",strerror(errno));
        return -1;
    }

    while(ptr = readdir(dp))
    {
        iMax = 0;
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path),"%s/%s", argv[1], ptr-> d_name);

        if (stat(path, &sobj) == -1)
            continue;

        if(S_ISDIR(sobj.st_mode))
        {
            continue;
        }

        printf("File name : %s\n",ptr->d_name);

        memset(Buffer, '\0', SIZE_BUFFER);

        fd = open(ptr -> d_name,O_RDONLY);
    
        if(fd < 0)
        {
            printf("Unable to open the file\n");
            printf("Reson : %s\n",strerror(errno));
            return -1;
        }

        while((iRet = read(fd, Buffer, SIZE_BUFFER)) > 0)
        {          
            iMax = iMax + iRet; 
        }

        printf("%ld bytes gets succesfully read\n",iMax);

        
        if(iMax > Large_iMax)
        { 
            Large_iMax = iMax;
            Large_fileName = ptr->d_name;

        }
        
    }

    
    printf("Largest file  is : %s\n", Large_fileName);
    printf("Bytes in the Largest file are : %ld\n", Large_iMax);
    
    closedir(dp);

    return 0;
}