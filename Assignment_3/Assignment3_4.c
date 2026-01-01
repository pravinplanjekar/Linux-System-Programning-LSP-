/*
Delete All Empty Regular Files
•Accept directory name.
•Delete les with size = 0 bytes (regular les only).
•Print names deleted + total deleted count.
*/

#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<dirent.h>


int main(int argc, char *argv[])
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    struct stat sobj;
    int Ret = 0;
    int Del_Count = 0;
    char SrcPath[1024];

    if(argc != 2)
    {
        printf("Invalid Arguments...\n");
        return -1;
    }
    
    dp = opendir(argv[1]);

    if(dp == NULL)
    {
        printf("Open : %s\n",strerror(errno));
        return -1;
    }

    // if (stat(argv[1], &sobj) == -1)
    // {
    //     printf("Error: %s\n", strerror(errno));
    //     return -1;
    //   }

    while((ptr = readdir(dp)) != NULL)
    {
        snprintf(SrcPath, sizeof(SrcPath), "%s/%s", argv[1], ptr->d_name);

        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
        {
            continue;
        }

        // if (stat(argv[1], &sobj) == -1)
        // {            Ret = unlink(SrcPath);
        
        //     printf("Error: %s\n", strerror(errno));
        //     return -1;
        // }

        if (lstat(SrcPath, &sobj) == -1)
        {
            // skip this entry and continue
            continue;
        }

        if(S_ISREG(sobj.st_mode) && sobj.st_size == 0)
        {
            if(unlink(SrcPath) == 0)
            {
            printf("Deleted : %s\n", ptr-> d_name);
            Del_Count++;
            }
        }

    }

    closedir(dp);

    printf("Total Deleted files : %d\n", Del_Count);

    return 0;

}