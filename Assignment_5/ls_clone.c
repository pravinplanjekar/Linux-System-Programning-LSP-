/*
1 Directory Traversal Basics
Create a program ls_clone.c that takes one directory path and prints:
•Entry name
•Type ( le/dir/link/other)
•Size (bytes)
•Permissions in rwxr-xr-x format
•Last modi ed time
•Skip . and ...
•Build full path using snprintf(dir + "/" + name).
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>

///////////////////////////////////////////////////////////
static const char* file_type(mode_t m)
{
    if (S_ISREG(m))  return "file";
    if (S_ISDIR(m))  return "dir";
    if (S_ISLNK(m))  return "link";
    return "other";
}
//////////////////////////////////////////////////////////

static void perms_to_str(mode_t m, char out[10])
{
    out[1] = (m & S_IRUSR) ? 'r' : '-';
    out[2] = (m & S_IWUSR) ? 'w' : '-';
    out[3] = (m & S_IXUSR) ? 'x' : '-';
    out[4] = (m & S_IRGRP) ? 'r' : '-';
    out[5] = (m & S_IWGRP) ? 'w' : '-';
    out[6] = (m & S_IXGRP) ? 'x' : '-';
    out[7] = (m & S_IROTH) ? 'r' : '-';
    out[8] = (m & S_IWOTH) ? 'w' : '-';
    out[9] = (m & S_IXOTH) ? 'x' : '-';
    out[10] = '\0';
}
/////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{

    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    struct stat sobj;
    char path[4096];
    char perms[11];
    char buffer[64];


    if (argc != 2)
    {
        printf("Invalid Arguments...\n");
        return 1;
    }

    dp = opendir(argv[1]);

    if(dp == NULL)
    {
        printf("Open : %s\n",strerror(errno));
        return -1;
    }

    printf("%-30s %-6s %-12s %-11s %-20s\n",
           "NAME", "TYPE", "SIZE(bytes)", "PERMS", "MODIFIED");
    printf("--------------------------------------------------------------------------------\n");


     while ((ptr = readdir(dp)) != NULL)
    {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;

        
        snprintf(path, sizeof(path), "%s/%s", argv[1], ptr->d_name);

        if (lstat(path, &sobj) == -1)
        {
            fprintf(stderr, "lstat failed for %s: %s\n", path, strerror(errno));
            continue;
        }
    

//////////////////////////////////////////////////////////

    perms_to_str(sobj.st_mode, perms);

//////////////////////////////////////////////////////////

    struct tm *tm_info = localtime(&sobj.st_mtime);

    if (tm_info)
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
        else
            snprintf(buffer, sizeof(buffer), "N/A");

        printf("%-30s %-6s %-12lld %-11s %-20s\n",
               ptr->d_name,
               file_type(sobj.st_mode),
               (long long)sobj.st_size,
               perms + 1,        
               buffer);

//////////////////////////////////////////////////////////

    }


    closedir(dp);

    return 0;
}