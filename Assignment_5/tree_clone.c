/*
2 Recursive Directory Traversal
Write tree_clone.c which prints a directory as a tree, like:
root/
a.txt
src/
Ganesh.c
•Indentation based on recursion depth
•Print type markers:
◦[D] directory
◦[F] regular le
◦[L] symbolic link
•Use lstat() to detect symbolic links.
•Do not follow symlink directories (avoid loops).
*/

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define PATH_MAX_LEN 4096

//////////////////////////////////////////////////////////////////

static void print_indent(int depth)
{
    
    for (int i = 0; i < depth; i++)
        printf("    ");
}

//////////////////////////////////////////////////////////////

static const char* marker(mode_t m)
{
    if (S_ISDIR(m))  return "[D]";
    if (S_ISREG(m))  return "[F]";
    if (S_ISLNK(m))  return "[L]";
    return "[?]";
}

/////////////////////////////////////////////////////////////

static void tree_walk(const char *dirpath, int depth)
{
    DIR *dp = NULL;
    struct dirent *ptr = NULL;
    struct stat sobj;
    char fullpath[PATH_MAX_LEN];

    dp = opendir(dirpath);
    if (dp == NULL)
    {
        print_indent(depth);
        printf("Cannot open: %s (%s)\n", dirpath, strerror(errno));
        return;
    }

    while ((ptr = readdir(dp)) != NULL)
    {
//////////////////////////////////////////////////////////////
        // Skip . and ..
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;

/////////////////////////////////////////////////////////////

        // Build full path
        if (snprintf(fullpath, sizeof(fullpath), "%s/%s", dirpath, ptr->d_name) >= (int)sizeof(fullpath))
        {
            print_indent(depth);
            printf("Path too long: %s/%s\n", dirpath, ptr->d_name);
            continue;
        }

//////////////////////////////////////////////////////////////

        if (lstat(fullpath, &sobj) == -1)
        {
            print_indent(depth);
            printf("! lstat failed: %s (%s)\n", ptr->d_name, strerror(errno));
            continue;
        }

        
        print_indent(depth);
        printf("%s %s", marker(sobj.st_mode), ptr->d_name);

        
        if (S_ISDIR(sobj.st_mode))
            printf("/");

        printf("\n");

        
        if (S_ISDIR(sobj.st_mode))
        {
            tree_walk(fullpath, depth + 1);
        }
    }

    closedir(dp);
}

//////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    struct stat sobj;


/////////// ARGUMENT VALIDATION////////////////////////////////

    if (argc != 2)
    {
        printf("Invalid Arguments...\n");
        return -1;
    }
////////////////////////////////////////////////////////////////


    if (lstat(argv[1], &sobj) == -1)
    {
        printf("lstat error: %s\n", strerror(errno));
        return 1;
    }
////////////////////////////////////////////////////////////////// 

    if (!S_ISDIR(sobj.st_mode))
    {
        printf("Error: %s is not a directory\n", argv[1]);
        return 1;
    }


//////// Print root//////////////////////////////////////
    printf("[D] %s/\n", argv[1]);

///////// Walk /////////////////////////////////////////

    tree_walk(argv[1], 1);

///////////////////////////////////////////////////////

    return 0;
}