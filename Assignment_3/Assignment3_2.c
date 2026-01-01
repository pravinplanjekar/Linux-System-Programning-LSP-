/*
Check File Present in Directory
•Accept directory name and le name.
•Check whether that file exists in that directory.
•Print absolute matched path if found.
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<dirent.h>
#include<errno.h>
#include<stdbool.h>


int main(int argc, char *argv[])
{
    DIR *dp = NULL;
    struct stat D_sobj;
    struct stat F_sobj;
    struct dirent *ptr = NULL;
    bool Flag = false;
    char path[1024];

    //stat(argv[1],&D_sobj);
    if (stat(argv[1], &D_sobj) == -1)
    {
        printf("stat failed for '%s' : %s\n", argv[1], strerror(errno));
        return -1;
    }

    if(! S_ISDIR(D_sobj.st_mode))
        {
            printf("%s is not a Directory...\n", argv[1]);
            return -1;
        }
    
    //stat(argv[2],&F_sobj);
    
    if (stat(argv[2], &F_sobj) == -1)
    {
        printf("stat failed for '%s' : %s\n", argv[2], strerror(errno));
        return -1;
    }
    

    if(! S_ISREG(F_sobj.st_mode))
        {
            printf("%s is not a File...\n", argv[2]);
            return -1;
        }

    dp = opendir(argv[1]);
    if(dp == NULL)
    {
        printf("%s\n",strerror(errno));
        return -1;
    }

    while(ptr = readdir(dp))
    {

        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
        {
            continue;
        }

        if(strcmp(argv[2], ptr->d_name) == 0)
        {
            Flag = true;
        }
    }

    if(Flag == true)
    {
        printf("File exist in the Directory...\n");
    }
    else 
    {
        printf("File  does not exist in the Directory...\n");
    }
   
    return 0;

}