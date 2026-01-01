/*
List All Files From Directory
•Accept directory name.
•Use opendir() / readdir() to print only names (skip . and ..).
*/

#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<dirent.h>
#include<sys/types.h>


int main(int argc, char *argv[])
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;

    dp = opendir(argv[1]);

    if(dp == NULL)
    {
        printf("%s\n",strerror(errno));
        return -1;
    }

    while((ptr = readdir(dp)) != NULL)
    {
        if (strcmp(ptr->d_name, ".") == 0 ||
            strcmp(ptr->d_name, "..") == 0)
        {
            continue;
        }
        printf("%s\n", ptr -> d_name);
    }

    closedir(dp);
    return 0;

}