/*
3 File Counter + Size Report
Create dir_report.c that recursively calculates:
•Total number of files
•Total number of directories
•Total size of regular files (in bytes)
•Largest file name + size
•Count a directory when you enter it.
•For size: consider only regular files (S_ISREG).
•Ignore symlink target size (treat symlink as link object only).

Output:
Files: 120
Dirs : 15
Total Size: 9823412 bytes
Largest: Marvellous.mp4 (2341123 bytes)
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define PATH_MAX_LEN 4096

long long total_files = 0;
long long total_dirs  = 0;
long long total_size  = 0;

char largest_file[PATH_MAX_LEN] = "";
long long largest_size = 0;

// Recursive directory traversal
void traverse_dir(const char *dirpath)
{
    DIR *dp;
    struct dirent *ptr;
    struct stat sobj;
    char path[PATH_MAX_LEN];

    dp = opendir(dirpath);
    if (dp == NULL)
    {
        perror("opendir");
        return;
    }

/////////////////////////////////////////////////////////////

    // Count directory 
    total_dirs++;

//////////////////////////////////////////////////////////////

    while((ptr = readdir(dp)) != NULL)
    {
        // Skip . and .. 
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;

        // Build full path
        snprintf(path, sizeof(path), "%s/%s", dirpath, ptr->d_name);

        
        if (lstat(path, &sobj) == -1)
        {
            perror("lstat");
            continue;
        }

        // Check Regular file
        if (S_ISREG(sobj.st_mode))
        {
            total_files++;
            total_size += sobj.st_size;

            if (sobj.st_size > largest_size)
            {
                largest_size = sobj.st_size;
                strncpy(largest_file, ptr->d_name, sizeof(largest_file) - 1);
                largest_file[sizeof(largest_file) - 1] = '\0';
            }
        }
        
        else if (S_ISDIR(sobj.st_mode))
        {
            traverse_dir(path);
        }
    
    }

    closedir(dp);
}

int main(int argc, char *argv[])
{
    
    if (argc != 2)
    {
        //printf("Usage: %s <directory_path>\n", argv[0]);
        printf("Invalid Arguments...\n");

        return 1;
    }

    traverse_dir(argv[1]);

    printf("\n===== Directory Report =====\n");
    printf("Files       : %lld\n", total_files);
    printf("Dirs        : %lld\n", total_dirs);
    printf("Total Size  : %lld bytes\n", total_size);

    if (largest_size > 0)
        printf("Largest     : %s (%lld bytes)\n", largest_file, largest_size);
    else
        printf("Largest     : N/A\n");

    return 0;
}
